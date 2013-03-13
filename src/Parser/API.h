/************************************************************************
*
* Cxxi
* Licensed under the MIT license.
*
************************************************************************/

#define CXXI_API

#include <string>
#include <vector>

namespace Cxxi {

struct ParserOptions
{
    const char* FileName;
    std::vector<const char*> Defines;
    std::vector<const char*> IncludeDirs;
    int ToolSetToUse;
    bool Verbose;
};

struct ParserDiagnostic
{
    std::string FileName;
    std::string Message;
};

enum class ParserResultKind
{
    Success,
    FileNotFound,
    Error
};

namespace Bridge { struct Library; }

struct ParserResult
{
    ParserResultKind Kind;
    std::vector<ParserDiagnostic> Diagnostics;
    Bridge::Library* Library;
};

CXXI_API ParserResult Parse(const ParserOptions& Opts);

}