using CppSharp.AST;
using CppSharp.Generators;
using CppSharp.Utils;

namespace CppSharp.Tests
{
    public class Basic : LibraryTest
    {
        public Basic(LanguageGeneratorKind kind)
            : base("Basic", kind)
        {
        }

        public override void Preprocess(Driver driver, Library lib)
        {
            lib.SetClassAsValueType("Bar");
            lib.SetClassAsValueType("Bar2");
        }

        static class Program
        {
            public static void Main(string[] args)
            {
                ConsoleDriver.Run(new Basic(LanguageGeneratorKind.CPlusPlusCLI));
                ConsoleDriver.Run(new Basic(LanguageGeneratorKind.CSharp));
            }
        }
    }
}
