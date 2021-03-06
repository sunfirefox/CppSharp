## Main repository: https://github.com/mono/CppSharp

CppSharp is a library that allows you to generate .NET bindings that wrap C/C++ code allowing interoperability with managed languages. This can be useful if you have an existing native codebase and want to add scripting support, or want to consume an existing native library in your managed code.

## Getting started

Since binary releases have not been provided yet, you will have to compile the project and dependencies manually (LLVM and Clang). 

The documentation is still a work-in-progress, please see the following resources for more information:

[Getting Started](docs/GettingStarted.md)

[User's Manual](docs/UsersManual.md)

[Developer's Manual](docs/DevManual.md)

## Why reinvent the wheel?

There are not many automated binding tools around, the only real alternative is SWIG. So how is it different from SWIG?

 * No need to generate a C layer to interop with C++.
 * Based on an actual C++ parser (Clang) so very accurate.
 * Understands C++ at the ABI (application binary interface) level
 * Easily extensible semantics via user passes
 * Strongly-typed customization APIs
 * Can be used as a library

## Can I use it yet?

It is being used to bind "real-world" complex codebases successfully, so give it a shot.

Since C and C++ provide such a wide array of features I'm sure there's still tonnes of bugs and unsupported edge cases, but give and try and report any bugs you find and I'll try to fix them ASAP.


## Similiar Tools

* Sharppy - .NET bindings generator for unmanaged C++
[https://code.google.com/p/sharppy/](https://code.google.com/p/sharppy/)

* XInterop
[http://xinterop.com/](http://xinterop.com/)

* SWIG
[http://www.swig.org/](http://www.swig.org/)

* Cxxi
[https://github.com/mono/cxxi/](https://github.com/mono/cxxi/)
