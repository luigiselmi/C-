C/C++ for Numerical Methods and Scientific Applications
=======================================================
This repository contains programs in C/C++. The C/C++ source code can be compiled from
the command line or from an IDE such as [Eclipse CDT](https://www.eclipse.org/cdt/)

## Compile and execute from the command Line
The GNU g++ (or gcc) compiler for C and C++ is installed by default on any Linux OS and it
can be used from the command line. For the MS Windows OS the [Cygwin Project](https://www.cygwin.com/) provides a Linux environment with the GNU C/C++ compilers.
### Compile and link a C/C++ program
To compile a C source file you can use the GNU gcc compiler (or the cc compiler for C programs)

$ gcc HelloWorld.c

The output of the compilation by default is an executable file a.exe. In order to name the
executable file like the source code you can use the command

$ gcc HelloWorld.c -o HelloWorld

C++ source code can be compiled using the GNU g++ compiler.

### Run a program
To execute a program, HelloWorld.exe for instance, use the command

$ ./HelloWorld.exe

or simply

$ ./HelloWorld

## Eclipse CDT (C/C++ Development Tooling)
The main problem about developing using a text editor is that one cannot use the debugger.
Eclipse, the Java IDE, can be used to develop C/C++ application as well. One needs to install
Java in order to execute the IDE, then the compiler and the debugger. In Eclipse CDT an executable is created in a project that includes all the required C or C++ files, one of which contains the main() function. If a main() function is defined in more than a file in the project the IDE will raise an error of "multiple definitions of main". For this reason in Eclipse CDT each file containing a main() function should be in a separate project.
