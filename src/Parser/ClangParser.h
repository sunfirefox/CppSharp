/************************************************************************
*
* Cxxi
* Licensed under the MIT license.
*
************************************************************************/

#include "Parser.h"
#include "AST.h"

#include <llvm/Support/Host.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/IdentifierTable.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Mangle.h>
#include <clang/AST/RecordLayout.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Sema/Sema.h>
#include "CXXABI.h"

#include <string>
#include <cstdarg>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define Debug printf

namespace Cxxi {

struct Parser
{
    Parser(const ParserOptions& Opts);

    void Setup(const ParserOptions& Opts);
    ParserResult Parse(const std::string& File);

protected:

    // AST traversers
    void WalkAST();
    void WalkMacros(clang::PreprocessingRecord* PR);
    Bridge::Declaration* WalkDeclaration(clang::Decl* D, clang::TypeLoc* = 0,
        bool IgnoreSystemDecls = true, bool CanBeDefinition = false);
    Bridge::Declaration* WalkDeclarationDef(clang::Decl* D);
    Bridge::Enumeration* WalkEnum(clang::EnumDecl*);
    Bridge::Function* WalkFunction(clang::FunctionDecl*, bool IsDependent = false,
        bool AddToNamespace = true);
    Bridge::Class* WalkRecordCXX(clang::CXXRecordDecl*, bool IsDependent = false);
    Bridge::Method* WalkMethodCXX(clang::CXXMethodDecl*);
    Bridge::Field* WalkFieldCXX(clang::FieldDecl*, Bridge::Class*);
    Bridge::ClassTemplate* Parser::WalkClassTemplate(clang::ClassTemplateDecl*);
    Bridge::FunctionTemplate* Parser::WalkFunctionTemplate(
        clang::FunctionTemplateDecl*);
    Bridge::Variable* WalkVariable(clang::VarDecl*);
    Bridge::Type* WalkType(clang::QualType, clang::TypeLoc* = 0,
      bool DesugarType = false);

    // Clang helpers
    bool IsValidDeclaration(const clang::SourceLocation& Loc);
    std::string GetDeclMangledName(clang::Decl*, clang::TargetCXXABI,
        bool IsDependent = false);
    std::string GetTypeName(const clang::Type*);
    void HandleComments(clang::Decl* D, Bridge::Declaration*);
    void WalkFunction(clang::FunctionDecl* FD, Bridge::Function* F,
        bool IsDependent = false);

    Bridge::TranslationUnit* GetModule(clang::SourceLocation Loc);
    Bridge::Namespace* GetNamespace(const clang::NamedDecl*);

    Bridge::Library* Lib;
    unsigned Index;

    llvm::OwningPtr<clang::CompilerInstance> C;
    clang::ASTContext* AST;
};

//-----------------------------------//

typedef std::string String;

String StringFormatArgs(const char* str, va_list args);
String StringFormat(const char* str, ...);

}