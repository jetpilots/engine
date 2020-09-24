#include "jet_base.h"
#include "jet_sys_time.h"

typedef struct XMLAttr XMLAttr;
typedef struct XMLNode XMLNode;
typedef struct XMLParser XMLParser;

// if you want to use nan tagging
// for json / xml keep list<node>
// for yaml keep list<node*>
// for json/xml the value IS the list item, so no extra storage (no ptr to node)
// for yaml you may need refs to primitives (num/bool) so this cant happen

struct XMLAttr {
    const char* key;
    const char* val;
};

struct XMLNode {
    const char* tag;
    List(XMLAttr) * attributes;
    union {
        const char* text;
        List(XMLNode) * children;
    };
};

struct XMLParser {
    const char* filename;
    int line, col;
    char *data, *end;
    char* pos;
};

MKSTAT(XMLNode)
MKSTAT(XMLAttr)
MKSTAT(XMLParser)
