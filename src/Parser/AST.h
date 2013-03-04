/************************************************************************
*
* Cxxi
* Licensed under the MIT license.
*
************************************************************************/

#include <vector>

#define CXXI_API

// Types

struct TypeQualifiers
{
    bool IsConst;
    bool IsVolatile;
    bool IsRestrict;
};

struct Type
{
};

struct QualifiedType
{
    Type Type;
    TypeQualifiers Qualifiers;
};

struct Declaration;

struct TagType : Type
{
    Declaration* Declaration;
};

enum class ArraySize
{
    Constant,
    Variable
};

struct ArrayType : Type
{
    QualifiedType Type;
    ArraySize SizeType;
    long Size;
};

struct Parameter;

struct FunctionType : Type
{
    QualifiedType ReturnType;
    std::vector<Parameter*> Parameters;
};

enum struct TypeModifier
{
    Value,
    Pointer,
    LVReference,
    RVReference
};

struct PointerType : Type
{
    QualifiedType Pointee;
    TypeModifier Modifier;
};

struct MemberPointerType : Type
{
    QualifiedType Pointee;
};

struct TypedefDecl;

struct TypedefType
{
    TypedefDecl* Declaration;
};

enum struct TemplateArgumentKind
{
    Type,
    Declaration,
    NullPtr,
    Integral,
    Template,
    TemplateExpansion,
    Expression,
    Pack
};

struct TemplateArgument
{
    TemplateArgumentKind Kind;
    QualifiedType Type;
    Declaration* Declaration;
    long Integral;
};

struct Template;

struct TemplateSpecializationType : Type
{
    std::vector<TemplateArgument> Arguments;
    Template* Template;
};

struct TemplateParameter
{
    const char* Name;
};

struct TemplateParameterType : Type
{
    TemplateParameter Parameter;
    Template* Template;
};

// Declarations

struct Namespace;

struct Declaration
{
    Namespace* Namespace;
    const char* Name;
    const char* Comment;
    unsigned DefinitionOrder;
};

struct Parameter : Declaration
{
    Type* Type;
};

struct Function : Declaration
{
    Type* ReturnType;
    bool IsVariadic;
    bool IsInline;
    const char* Mangled;
};

enum struct CXXMethodKind
{
    Normal,
    Constructor,
    Destructor,
    Conversion,
    Operator,
    UsingDirective
};

enum struct CXXOperatorKind
{
    None,
    New,
    Delete,
    Array_New,
    Array_Delete,
    Plus,
    Minus,
    Star,
    Slash,
    Percent,
    Caret,
    Amp,
    Pipe,
    Tilde,
    Exclaim,
    Equal,
    Less,
    Greater,
    PlusEqual,
    MinusEqual,
    StarEqual,
    SlashEqual,
    PercentEqual,
    CaretEqual,
    AmpEqual,
    PipeEqual,
    LessLess,
    GreaterGreater,
    LessLessEqual,
    GreaterGreaterEqual,
    EqualEqual,
    ExclaimEqual,
    LessEqual,
    GreaterEqual,
    AmpAmp,
    PipePipe,
    PlusPlus,
    MinusMinus,
    Comma,
    ArrowStar,
    Arrow,
    Call,
    Subscript,
    Conditional
};

struct Method : Function
{

};

struct Enumeration : Declaration
{

};

enum struct AccessSpecifier
{
    Private,
    Protected,
    Public
};

struct BaseClassSpecifier
{
    AccessSpecifier Access;
    bool IsVirtual;
    Type *Type;
};

struct Class : Declaration
{
    std::vector<BaseClassSpecifier> Bases;
};

struct Field : Declaration
{
};

struct ClassTemplate : Declaration
{
};

struct FunctionTemplate : Declaration
{
};

struct Variable : Declaration
{
};

struct Namespace : Declaration
{
};

struct TranslationUnit
{
};
