#include "XML.h"

int main(int argc, char* argv[])
{
    //     char* xmlstr = "" //
    //                    "<xml>" //
    //                    "  <head>" //
    //                    "    <title attr=value attr2=\"value2 what>\">" //
    //                    "    </title>" //
    //                    "    <meta name=content-type content=utf-8/>" //
    //                    "  </head>" //
    //                    "</xml>"; //
    //     "<foot>" //
    //     "</foot>";
    //     xmlstr = "<meta name=content-type content=utf-8/><meta name=keywords
    //     content='rail,train,goods'/>"; xmlstr = "<a>"; xmlstr = "<a></a>";

    // xmlstr = "<?xml version='1.0'?>"
    //          "<Tests xmlns='http://www.adatum.com'>"
    //          "<Test TestId='0001' TestType='CMD'>"
    //          "<Name>Convert number to string</Name>"
    //          "<CommandLine>Examp1.EXE</CommandLine>"
    //          "<Input>1</Input>"
    //          "<Output>One</Output>"
    //          "</Test>"
    //          "<Test TestId='0002' TestType='CMD'>"
    //          "<Name>Find succeeding characters</Name>"
    //          "<CommandLine>Examp2.EXE</CommandLine>"
    //          "<Input>abc</Input>"
    //          "<Output>def</Output>"
    //          "</Test>"
    //          "<Test TestId='0003' TestType='GUI'>"
    //          "<Name>Convert multiple numbers to strings</Name>"
    //          "<CommandLine>Examp2.EXE /Verbose</CommandLine>"
    //          "<Input>123</Input>"
    //          "<Output>One Two Three</Output>"
    //          "</Test>"
    //          "<Test TestId='0004' TestType='GUI'>"
    //          "<Name>Find correlated key</Name>"
    //          "<CommandLine>Examp3.EXE</CommandLine>"
    //          "<Input>a1</Input>"
    //          "<Output>b1</Output>"
    //          "</Test>"
    //          "<Test TestId='0005' TestType='GUI'>"
    //          "<Name>Count characters</Name>"
    //          "<CommandLine>FinalExamp.EXE</CommandLine>"
    //          "<Input>This is a test</Input>"
    //          "<Output>14</Output>"
    //          "</Test>"
    //          "<Test TestId='0006' TestType='GUI'>"
    //          "<Name>Another Test</Name>"
    //          "<CommandLine>Examp2.EXE</CommandLine>"
    //          "<Input>Test Input</Input>"
    //          "<Output>10</Output>"
    //          "</Test>"
    //          "</Tests>";

    // XMLParser *par = XMLParser_fromStringClone(xmlstr);
    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    jet_sys_time_Time t0; // = jet_sys_time_getTime();
    XMLParser* par = XMLParser_fromFile(argv[1]);
    double tms; // = jet_sys_time_clockSpanMicro(t0) / 1.0e3;
    // eprintf("\e[1mread time:\e[0m %.1f ms (%.2f GB/s)\n", tms,
    //     1 / ((tms / 1e3) * 1e9 / (par->end - par->data))); // sw.print();

    t0 = jet_sys_time_getTime();
    List(XMLNode)* parsed = XMLParser_parseTags(par);
    if (argc > 2 && *argv[2] == 'x') XMLNodeList_print(parsed, 0);
    if (argc > 2 && *argv[2] == 'f') FMLNodeList_print(parsed, 0, 0);

    tms = jet_sys_time_clockSpanMicro(t0) / 1.0e3;

    eputs("-------------------------------------------------------"
          "\n");
    allocstat(XMLAttr);
    allocstat(XMLParser);
    allocstat(XMLNode);
    allocstat(jet_PtrList);
    eputs("-------------------------------------------------------"
          "\n");
    eprintf("*** Total size of nodes                     = %7d B\n",
        jet_gPool->usedTotal);
    eprintf("*** Space allocated for nodes               = %7d B\n",
        jet_gPool->capTotal);
    eprintf("*** Node space utilisation                  = %7.1f %%\n",
        jet_gPool->usedTotal * 100.0 / jet_gPool->capTotal);
    eputs("-------------------------------------------------------"
          "\n");
    eprintf("*** File size                               = %7lu B\n",
        par->end - par->data);
    eprintf("*** Node size to file size ratio            = %7.1f x\n",
        jet_gPool->usedTotal * 1.0 / (par->end - par->data));
    eputs("-------------------------------------------------------"
          "\n");
    eprintf("*** Space used for strings                  = %7u B\n",
        jet_sPool->usedTotal);
    eprintf("*** Allocated for strings                   = %7u B\n",
        jet_sPool->capTotal);
    eprintf("*** Space utilisation                       = %7.1f %%\n",
        jet_sPool->usedTotal * 100.0 / jet_sPool->capTotal);
    eputs("-------------------------------------------------------"
          "\n");
    eputs("\e[1mMemory-related calls\e[0m\n");
    eprintf("  calloc: %-7d | malloc: %-7d | realloc: %-7d\n",
        jet_globals__callocCount, jet_globals__mallocCount,
        jet_globals__reallocCount);
    eprintf("  strlen: %-7d | strdup: %-7d |\n", jet_globals__strlenCount,
        jet_globals__strdupCount);

    eprintf("\e[1mTime elapsed:\e[0m %.1f ms (%.2f GB/s)\n", tms,
        1 / ((tms / 1e3) * 1e9 / (par->end - par->data))); // sw.print();

    return 0;
}
