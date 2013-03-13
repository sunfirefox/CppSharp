/************************************************************************
*
* Cxxi
* Licensed under the MIT license.
*
************************************************************************/

#include <vector>

#define CXXI_API

namespace Cxxi { namespace Bridge {

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
    Type* Type;
    TypeQualifiers Qualifiers;
};

enum class PrimitiveType
{
    Null,
    Void,
    Bool,
    WideChar,
    Int8,
    Char = Int8,
    UInt8,
    UChar = UInt8,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Int64,
    UInt64,
    Float,
    Double
};

struct BuiltinType : public Type
{
    PrimitiveType Type;
};

struct Declaration;

struct TagType : public Type
{
    Declaration* Declaration;
};

enum class ArrayTypeSize
{
    Constant,
    Variable
};

struct ArrayType : public Type
{
    QualifiedType QualifiedType;
    ArrayTypeSize SizeType;
    long Size;
};

struct Parameter;

struct FunctionType : public Type
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

struct PointerType : public Type
{
    QualifiedType QualifiedPointee;
    TypeModifier Modifier;
};

struct MemberPointerType : public Type
{
    QualifiedType Pointee;
};

struct TypedefDecl;

struct TypedefType : public Type
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

struct TemplateSpecializationType : public Type
{
    std::vector<TemplateArgument> Arguments;
    Template* Template;
};

struct TemplateParameter
{
    const char* Name;
};

struct TemplateParameterType : public Type
{
    TemplateParameter Parameter;
    Template* Template;
};

// Declarations

struct Namespace;

struct Declaration
{
    Namespace* Namespace;
    std::string Name;
    std::string BriefComment;
    std::string DebugText;
    unsigned DefinitionOrder;
    bool IsIncomplete;
};

struct TypedefDecl : public Declaration
{
    QualifiedType QualifiedType;
};

struct Parameter : public Declaration
{
    QualifiedType QualifiedType;
    bool HasDefaultValue;
};

enum class CallingConvention
{
    Default,
    C,
    StdCall,
    ThisCall,
    FastCall,
    Unknown
};

struct Function : public Declaration
{
    Type* ReturnType;
    bool IsVariadic;
    bool IsInline;
    std::string Mangled;
    CallingConvention CallingConvention;
    std::vector<Parameter*> Parameters;
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

enum struct AccessSpecifier
{
    Private,
    Protected,
    Public
};

struct Method : public Function
{
    AccessSpecifier Access;

    bool IsVirtual;
    bool IsStatic;
    bool IsConst;
    bool IsImplicit;

    CXXMethodKind Kind;
    CXXOperatorKind OperatorKind;

    bool IsDefaultConstructor;
    bool IsCopyConstructor;
    bool IsMoveConstructor;
};

enum struct EnumModifiers
{
    Anonymous = 1 << 0,
    Scoped = 1 << 1,
    Flags  = 1 << 2,
};

struct EnumItem : public Declaration
{
    std::string Name;
    long Value;
};

struct Enumeration : public Declaration
{
    EnumModifiers Modifiers;
    QualifiedType QualifiedType;
    BuiltinType* BuiltinType;
    std::vector<EnumItem> Items;
};

struct Variable : public Declaration
{
};

struct BaseClassSpecifier
{
    AccessSpecifier Access;
    bool IsVirtual;
    Type* Type;
};

struct Class;

struct Field : public Declaration
{
    QualifiedType QualifiedType;

    AccessSpecifier Access;
    unsigned Offset;
    Class* Class;
};

struct Class : public Declaration
{
    std::vector<BaseClassSpecifier*> Bases;
    std::vector<Field*> Fields;
    std::vector<Method*> Methods;

    bool IsPOD;
    bool IsAbstract;
    bool IsUnion;
};

struct Template : public Declaration
{
};

struct ClassTemplate : public Template
{
    Declaration* TemplatedDecl;
};

struct ClassTemplateSpecialization : public Declaration
{
};

struct ClassTemplatePartialSpecialization : public Declaration
{
};

struct FunctionTemplate : public Template
{
    Declaration* TemplatedDecl;
};

struct Namespace : public Declaration
{
    Class* FindClass(const std::string& Name, bool IsComplete,
        bool Create = false)
    {
        return 0;
    }

    Class* FindClass(const std::string& Name, bool Create = false)
    {
        return 0;
    }

    Enumeration* FindEnum(const std::string& Name, bool Create = false)
    {
        return 0;
    }

    Function* FindFunction(const std::string& Name, bool Create = false)
    {
        return 0;
    }

    TypedefDecl* FindTypedef(const std::string& Name, bool Create = false)
    {
        return 0;
    }

    Namespace* FindCreateNamespace(const std::string& Name, Namespace* Parent)
    {
        return 0;
    }

    std::vector<Namespace*> Namespaces;
    std::vector<Enumeration*> Enums;
    std::vector<Function*> Functions;
    std::vector<Enumeration*> Classes;
    std::vector<ClassTemplate*> ClassTemplates;
    std::vector<FunctionTemplate*> FunctionTemplates;
    std::vector<TypedefDecl*> Typedefs;
};

struct MacroDefinition : public Declaration
{
    std::string Expression;
};

struct TranslationUnit : public Namespace
{
    std::string FileName;
    bool IsSystemHeader;
    std::vector<Namespace*> Namespaces;
    std::vector<MacroDefinition*> Macros;
};

struct Library
{
    TranslationUnit* FindOrCreateModule(const std::string& File)
    {
        return 0;
    }

    std::vector<TranslationUnit*> Units;
};

} }