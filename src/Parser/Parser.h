/************************************************************************
*
* Cxxi
* Licensed under the simplified BSD license. All rights reserved.
*
************************************************************************/

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

struct ParserOptions
{
    const char* FileName;
};

struct ParserResult
{

};

struct Parser
{
    Parser(const ParserOptions& Opts);

    void Setup(const ParserOptions& Opts);
    ParserResult Parse(const std::string& File);

protected:

    // AST traversers
    void WalkAST();
    void WalkMacros(clang::PreprocessingRecord* PR);
    Declaration WalkDeclaration(clang::Decl* D, clang::TypeLoc* = 0,
        bool IgnoreSystemDecls = true, bool CanBeDefinition = false);
    Declaration WalkDeclarationDef(clang::Decl* D);
    Enumeration WalkEnum(clang::EnumDecl*);
    Function WalkFunction(clang::FunctionDecl*, bool IsDependent = false,
        bool AddToNamespace = true);
    Class WalkRecordCXX(clang::CXXRecordDecl*, bool IsDependent = false);
    Method WalkMethodCXX(clang::CXXMethodDecl*);
    Field WalkFieldCXX(clang::FieldDecl*, Cxxi::Class^);
    ClassTemplate Parser::WalkClassTemplate(clang::ClassTemplateDecl*);
    FunctionTemplate Parser::WalkFunctionTemplate(
        clang::FunctionTemplateDecl*);
    Variable WalkVariable(clang::VarDecl*);
    Type WalkType(clang::QualType, clang::TypeLoc* = 0,
      bool DesugarType = false);

    // Clang helpers
    bool IsValidDeclaration(const clang::SourceLocation& Loc);
    std::string GetDeclMangledName(clang::Decl*, clang::TargetCXXABI,
        bool IsDependent = false);
    std::string GetTypeName(const clang::Type*);
    void HandleComments(clang::Decl* D, Cxxi::Declaration^);
    void WalkFunction(clang::FunctionDecl* FD, Cxxi::Function^ F,
        bool IsDependent = false);

    TranslationUnit GetModule(clang::SourceLocation Loc);
    Namespace GetNamespace(const clang::NamedDecl*);

    llvm::OwningPtr<clang::CompilerInstance> C;
    clang::ASTContext* AST;
};

//-----------------------------------//

typedef std::string String;

String StringFormatArgs(const char* str, va_list args);
String StringFormat(const char* str, ...);
