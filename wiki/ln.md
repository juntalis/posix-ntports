## Ln.exe (Or Something like that)

This is a (WIP) Win32 implementation of the GNU ln utility supporting both native links (symbolic/hard/junctions), as well as cygwin-style symlinks. I'm aiming to have the command-line arguments identical to that of the GNU utility, thus allowing it to be used in configure/build scripts without any modifications.

Since I'm currently using Microsoft VC Compiler 2010, I know it compiles with that. Let me know if you have issues with another compiler, however, and I'll see what I can do.

Anything you find here that I wrote, you can consider released under the Do What The Fuck You Want To Public License. (WTFPL)

#### From Command Prompt

The program will automatically translate the paths specified, allowing you to use whatever directory separators you want. Like ln, it will create relative symbolic links if the target is specified as a relative target.

	G:\cpp.workspace\ln-win\src\bin>ln.exe -s G:\cpp.workspace\tools\unifdef\unifdef.exe unifdef.exe
	unifdef.exe was created successfully.

	G:\cpp.workspace\ln-win\src\bin>ln.exe unifdef.exe unifdef2.exe
	unifdef2.exe was created successfully.
	
	G:\cpp.workspace\ln-win\src\bin>ln.exe -s ../../src/msyspath/msyspath.exe msyspath.exe
	msyspath.exe was created successfully.
	
	G:\cpp.workspace\ln-win\src\bin>ln.exe -s ..\..\src\msyspath\msyspath.exe msyspath2.exe
	msyspath2.exe was created successfully.

And just to test, I wrote up a quick python script that makes ctypes calls to [reparselib](https://github.com/amdf/reparselib) to read info associated with reparse points. (Like symbolic links)

	G:\cpp.workspace\ln-win\src\bin>readlink.py unifdef.exe unifdef2.exe msyspath.exe msyspath2.exe

	File: unifdef.exe
	  ReparsePointExists(unifdef.exe) True
	  IsSymbolicLink(unifdef.exe) True
	  IsSymbolicLinkRelative(unifdef.exe) False
	  IsJunctionPoint(unifdef.exe) False
	  IsMountPoint(unifdef.exe) False
	  GetPrintName(unifdef.exe, outbuf, 260) True
			outbuf => G:\cpp.workspace\tools\unifdef\unifdef.exe
	  GetSubstituteName(unifdef.exe, outbuf, 260) True
			outbuf => \??\G:\cpp.workspace\tools\unifdef\unifdef.exe

	File: unifdef2.exe
	  ReparsePointExists(unifdef2.exe) False
	  IsSymbolicLink(unifdef2.exe) False
	  IsSymbolicLinkRelative(unifdef2.exe) False
	  IsJunctionPoint(unifdef2.exe) False
	  IsMountPoint(unifdef2.exe) False
	  GetPrintName(unifdef2.exe, outbuf, 260) False
			outbuf =>
	  GetSubstituteName(unifdef2.exe, outbuf, 260) False
			outbuf =>

	File: msyspath.exe
	  ReparsePointExists(msyspath.exe) True
	  IsSymbolicLink(msyspath.exe) True
	  IsSymbolicLinkRelative(msyspath.exe) True
	  IsJunctionPoint(msyspath.exe) False
	  IsMountPoint(msyspath.exe) False
	  GetPrintName(msyspath.exe, outbuf, 260) True
			outbuf => ..\msyspath\msyspath.exe
	  GetSubstituteName(msyspath.exe, outbuf, 260) True
			outbuf => ..\msyspath\msyspath.exe

	File: msyspath2.exe
	  ReparsePointExists(msyspath2.exe) True
	  IsSymbolicLink(msyspath2.exe) True
	  IsSymbolicLinkRelative(msyspath2.exe) True
	  IsJunctionPoint(msyspath2.exe) False
	  IsMountPoint(msyspath2.exe) False
	  GetPrintName(msyspath2.exe, outbuf, 260) True
			outbuf => ..\msyspath\msyspath.exe
	  GetSubstituteName(msyspath2.exe, outbuf, 260) True
			outbuf => ..\msyspath\msyspath.exe


You'll find the above script in the thirdparty/reparselib folder.

You'll notice that unifdef2.exe does not show up as a reparse point. As of yet, I'm still unaware of a way to read the target of hard links outside of explorer.

#### From Cygwin

Users can also create cygwin-style symbolic links through use of the -c flag.

	[Charles@Charles-PC ln]
	$ ./ln.exe -c /usr/local/bin/python2.7.exe /home/Charles/bin/python.exe
	C:\ShellEnv\home\Charles\bin\python.exe was created successfully.

	[Charles@Charles-PC ln]
	$ readlink /home/Charles/bin/python.exe
	/usr/local/bin/python2.7.exe

Or if you'd rather continue using native NTFS links, you can also specify filepaths in the cygwin format and have the program automatically convert them.

	[Charles@Charles-PC bin]
	$ ./ln.exe /usr/local/bin/python2.7.exe -s ./python2.7.exe
	.\python2.7.exe was created successfully.

And back in command prompt:

	G:\cpp.workspace\ln-win\src\bin>readlink.py python2.7.exe

	File: python2.7.exe
	  ReparsePointExists(python2.7.exe) True
	  IsSymbolicLink(python2.7.exe) True
	  IsSymbolicLinkRelative(python2.7.exe) False
	  IsJunctionPoint(python2.7.exe) False
	  IsMountPoint(python2.7.exe) False
	  GetPrintName(python2.7.exe, outbuf, 260) True
			outbuf => C:\ShellEnv\usr\local\bin\python2.7.exe
	  GetSubstituteName(python2.7.exe, outbuf, 260) True
			outbuf => \??\C:\ShellEnv\usr\local\bin\python2.7.exe

To use cygwin-functionality, you must actively be in a Cygwin shell to do so. Invoking the -c flag when in command prompt or trying to give ln.exe a cygwin path will simply give you an error.

	G:\cpp.workspace\ln-win\src\bin>.\ln.exe -c "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\cl.exe" "cl.exe"
	To create cygwin-style symbolic links, you must be in a cygwin shell.

As I said, it's still a work in progress. Not all command-line arguments have been implemented yet, and some of the "logic" based args unfortunately cannot be ported to Windows.

#### MSYSPath

I was originally intending to have the program detect MSYS environments, and automatically convert the paths for it, as well. The problem is, when I attempted to initialize the MSYS environment from the context of a non-MSYS application, it caused some kind of access error. (See [https://sourceforge.net/mailarchive/forum.php?thread_name=CA%2Bsc5mk_9K%2BMQ6ubSgdvDOFb5B0rYKdzR%2BEwh4M_c5wtmNwnTw%40mail.gmail.com&forum_name=mingw-users](here) for more information)

Anyways, in the process of trying to find a workaround, I wrote this quick little utility to implements some of the more basic functionality of cygpath. I intended to use it to convert paths at run-time, but I soon came to find that msys does that for itself.