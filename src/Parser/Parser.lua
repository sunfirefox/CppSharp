clang_msvc_flags =
{
  "/wd4146", "/wd4244", "/wd4800", "/wd4345",
  "/wd4355", "/wd4996", "/wd4624", "/wd4291"
}

config = { ManagedParser = false }

project "Parser"
  
  kind "SharedLib"
  language "C++"
  SetupNativeProject()
  
  dependson { "Bridge" }
  flags { common_flags }

  -- usingdirs is only supported in per-file configs in our
  -- premake build. remove this once this support is added
  -- at the project level.

  if config.ManagedParser then
    configuration { "*Main.cpp" }
      flags { "Managed" }
      usingdirs { libdir }
      
    configuration { "*Parser.cpp" }
      flags { "Managed" }
      usingdirs { libdir }
  end

  configuration "vs*"
    buildoptions { clang_msvc_flags }
    files { "VSLookup.cpp" }

  configuration "*"
  
  files
  {
    "**.h",
    "Main.cpp",
    "Parser.cpp",
    "**.lua"
  }
  
  includedirs
  {
    "../../deps/LLVM/include",
    "../../deps/LLVM/build/include",
    "../../deps/LLVM/tools/clang/include",
    "../../deps/LLVM/build/tools/clang/include"
  }
  
  configuration "Debug"
    libdirs { "../../deps/LLVM/build/lib/Debug" }

  configuration "Release"
    libdirs { "../../deps/LLVM/build/lib/RelWithDebInfo" }
  
  configuration "*"
  
  links
  {
    "LLVMSupport",
    "LLVMAsmParser",
    "LLVMBitReader",
    "LLVMBitWriter",
    "LLVMMC",
    "LLVMMCParser",
    "LLVMX86AsmParser",
    "LLVMX86AsmPrinter",
    "LLVMX86Desc",
    "LLVMX86Info",
    "LLVMX86Utils",
    "clangAnalysis",
    "clangBasic",
    "clangAST",
    "clangDriver",
    "clangEdit",
    "clangFrontend",
    "clangLex",
    "clangParse",
    "clangSema",
    "clangSerialization"
  }