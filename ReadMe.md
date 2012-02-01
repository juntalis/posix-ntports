## POSIX NT Ports

Working on consolidating all of my existing MSVC implementations/ports of GNU/Linux utilities into a single solution. Currently includes:

* env
* [ln](https://github.com/Juntalis/posix-ntports/wiki/ln)
* [which](https://github.com/Juntalis/posix-ntports/wiki/which)
* [msyspath](https://github.com/Juntalis/posix-ntports/wiki/ln) (A MSYS-based tool featuring SOME of the features of the cygpath tool)

All projects are based on Visual C 2010. There is also a VC 2010 project for compiling [gengetopt](http://www.gnu.org/software/gengetopt/gengetopt.html) with the MSVC compiler. It uses code downloaded from the [GNU Win32 Project](http://www.gnu.org/software/gengetopt/gengetopt.html).

A lot of the tools use common headers, macros, and definitions, so I'm trying to eliminate the overlap and rewrite a lot of the code before I get back to completing the tools that aren't quite done.

I also need to update the individual readmes for anything that's changed, and write a custom VC 2010 build tool for using the MSYS gcc compiler for msyspath.
