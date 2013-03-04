/************************************************************************
*
* Cxxi
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

#include "Parser.h"
#include "Interop.h"

ParserResult Parse(ParserOptions Opts)
{
    if (!Opts.FileName)
        return ParserResult();

    Parser p(Opts);
    return p.Parse(Opts.FileName);
}