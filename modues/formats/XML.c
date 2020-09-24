#include "XML.h"

static XMLNode* XMLNode_new(const char* tag)
{
    XMLNode* ret = jet_new(XMLNode);
    ret->tag = tag;
    return ret;
}

static XMLNode* XMLNode_newText(const char* text)
{
    XMLNode* ret = jet_new(XMLNode);
    ret->tag = NULL;
    ret->text = text;
    return ret;
}

static XMLAttr* XMLAttr_new(const char* key, const char* value)
{
    XMLAttr* ret = jet_new(XMLAttr);
    ret->key = key;
    ret->val = value;
    return ret;
}

static XMLParser* XMLParser_fromStringClone(const char* str)
{
    XMLParser* par = jet_new(XMLParser);
    size_t len = strlen(str);
    par->data = pstrndup(str, len);
    par->pos = par->data;
    par->end = par->data + len;
    return par;
}

static XMLParser* XMLParser_fromFile(char* filename)
{
    size_t flen = strlen(filename);

    struct stat sb;
    if (stat(filename, &sb) != 0) {
        eprintf("F+: file '%s' not found.\n", filename);
        return NULL;
    } else if (S_ISDIR(sb.st_mode)) {
        eprintf("F+: '%s' is a folder; only files are accepted.\n", filename);
        return NULL;
    } else if (access(filename, R_OK) == -1) {
        eprintf("F+: no permission to read file '%s'.\n", filename);
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    assert(file);

    XMLParser* ret = jet_new(XMLParser);

    ret->filename = filename;
    // ret->noext = str_noext(filename);
    fseek(file, 0, SEEK_END);
    const size_t size = ftell(file);

    // if (size < FILE_SIZE_MAX) {
    ret->data = (char*)malloc(size);
    fseek(file, 0, SEEK_SET);
    if (fread(ret->data, size, 1, file) != 1) {
        eprintf("F+: the whole file '%s' could not be read.\n", filename);
        fclose(file);
        return NULL;
        // would leak if ret was malloc'd directly, but we have a pool
    }
    ret->end = ret->data + size;
    ret->pos = ret->data;

    fclose(file);
    return ret;
}

static bool isAnyOf(char ch, char* chars)
{
    while (*chars)
        if (*chars++ == ch) return true;
    return false;
}

static const char* findchars_fast(
    const char* buf, const char* buf_end, const char* chars, size_t chars_size)
{
    // *found = 0;
#if __SSE4_2__
    if (jet_likely(buf_end - buf >= 16)) {
        __m128i chars16 = _mm_loadu_si128((const __m128i*)chars);

        size_t left = (buf_end - buf) & ~15;
        do {
            __m128i b16 = _mm_loadu_si128((void*)buf);
            int r = _mm_cmpestri(chars16, chars_size, b16, 16,
                _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_ANY
                    | _SIDD_UBYTE_OPS);
            if (jet_unlikely(r != 16)) {
                buf += r;
                // *found = 1;
                break;
            }
            buf += 16;
            left -= 16;
        } while (jet_likely(left != 0));
    }
    return buf;
#else
    return buf + strcspn(buf, chars); // strpbrk(buf, chars);
#endif
}

static List(XMLAttr) * XMLParser_parseAttrs(XMLParser* parser)
{
    List(XMLAttr)* list = NULL;
    List(XMLAttr)** listp = &list;

    while (*parser->pos and *parser->pos != '>' and *parser->pos != '/'
        and *parser->pos != '?') {
        const char* name = parser->pos;
        while (*parser->pos != '=') parser->pos++;
        *parser->pos++ = 0; // trample =

        char* markers;
        if (isAnyOf(*parser->pos, "'\"")) {
            markers = (*parser->pos == '"') ? "\"" : "'";
            parser->pos++;
        } else {
            markers = " >/?\t\n";
        }

        const char* value = parser->pos;

        while (not isAnyOf(*parser->pos, markers)) parser->pos++;
        if (not isAnyOf(*parser->pos, "/?>"))
            *parser->pos++ = 0; // trample the marker if " or ' or spaces
        // ^ DON't trample the markers / or > here, because in the case of e.g.
        // <meta name=content-type content=utf8/>
        // it will trample the / not allowing the calling parseTags to
        // detect that the tag is self-closing. Let the caller trample.

        while (isAnyOf(*parser->pos, " \t\n"))
            *parser->pos++ = 0; // skip and trample whitespace

        XMLAttr* attr = XMLAttr_new(name, value);
        listp = jet_PtrList_append(listp, attr);
    }
    //    if (*parser->pos == '/') *parser->pos++ = 0;
    //    assert(*parser->pos == '>');
    //    *parser->pos++ = 0;
    // don't consume ending />, leave it at that
    return list;
}

static List(XMLNode) * XMLParser_parseTags(XMLParser* parser)
{
    List(XMLNode)* list = NULL;
    List(XMLNode)** listp = &list;

    while (parser->pos < parser->end) {
        switch (*parser->pos) {
        case ' ':
        case '\t':
        case '\n':
            parser->pos++;
            break;
        case '<': {
            *parser->pos++ = 0;

            bool noChild = false;

            if (*parser->pos == '/') { // closing tag here means empty content
                parser->pos++; // note that will be past </
                return list; // null if no elements were found at this level
            } else if (not strncasecmp(parser->pos, "[CDATA[", 6)) { // cdata
            } else { // opening tag
                XMLNode* node = XMLNode_new(parser->pos);
                while (not isAnyOf(*parser->pos, " />\n\t"))
                    parser->pos++; // SSE?

                if (*parser->pos == ' ') {
                    *parser->pos++ = 0;
                    while (*parser->pos == ' ') parser->pos++;
                    node->attributes = XMLParser_parseAttrs(parser);
                }
                while (*parser->pos == ' ') parser->pos++;

                switch (*parser->pos) {
                case '/':
                case '?':
                    *parser->pos++ = 0;
                    assert(*parser->pos == '>');
                    noChild = true;
                //  fall through
                case '>':
                    // tag has ended. parse children
                    *parser->pos++ = 0;
                    if (not noChild) {
                        node->children = XMLParser_parseTags(parser);

                        char* closingTag = parser->pos;
                        while (*parser->pos != '>') // SSE?
                            parser->pos++; // seek to end of closing tag
                        *parser->pos++ = 0;

#ifndef FP_XML_SKIP_CLOSING_CHECKS // this is about 10% runtime for a large file
                        if (not *closingTag) {
                            printf("error: found end of file, expected </%s>\n",
                                node->tag);
                            exit(1);
                        } else if (strcasecmp(closingTag, node->tag)) {
                            printf("error: found </%s>, expected </%s>\n",
                                closingTag, node->tag);
                            exit(1);
                        }
#endif
                    }
                    break;
                default:
                    eprintf("oops1: unexpected '%c' (\"%.16s\"...)\n",
                        *parser->pos, parser->pos);
                    break;
                }

                listp = jet_PtrList_append(listp, node);
            }
        } break;

        default:

        {
            char* text = parser->pos;
            // printf("oops2: unexpected '%c' (\"%.16s...\")\n", *parser->pos,
            // parser->pos);
            while (*parser->pos != '<' and parser->pos < parser->end)
                parser->pos++;
            // parser->pos = findchars_fast(parser->pos, parser->end, "<", 1);
            // relying on the </ detector state to trample the <
            XMLNode* textNode = XMLNode_newText(text);
            listp = jet_PtrList_append(listp, textNode);
        }
        }
    }
    if (parser->pos < parser->end) printf("error: data unparsed\n");
    return list;
}

static void XMLAttr_print(XMLAttr* attr, int indent)
{
    printf(" %s=\"%s\"", attr->key, attr->val);
}

static void XMLNode_print(XMLNode* node, int indent);
static void XMLNodeList_print(List(XMLNode) * nodeList, int indent)
{
    jet_foreach(XMLNode*, childNode, nodeList) XMLNode_print(childNode, indent);
}

static const char* const spaces
    = "                                                 ";
static void XMLNode_print(XMLNode* node, int indent)
{
    if (node->tag) {
        printf("%.*s<%s%s", indent, spaces, node->tag,
            node->attributes ? "" : node->children ? ">\n" : "/>\n");
        jet_foreach(XMLAttr*, attr, node->attributes)
            XMLAttr_print(attr, indent);
        if (node->attributes) printf("%s\n", node->children ? ">" : " />");
        XMLNodeList_print(node->children, indent + 2);
        if (node->children) printf("%.*s</%s>\n", indent, spaces, node->tag);
    } else {
        printf("%.*s%s\n", indent, spaces, node->text);
    }
}
