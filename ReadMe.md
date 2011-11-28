## Which for Windows

Simple which implementation for Windows, which a few minor changes.

#### Usage

	which [-h|-?] [-a] [-n] [-x] program

* -a       List all matches found. (Default: Show the first match and exit.) - NOT YET IMPLEMENTED
* -h,-?    Show usage text.
* -n       Do not print a newline after the resolved path. (Default: "<full path>\r\n")
* -x       Do not use the PATHEXT variable to add extensions. (Default: Use PATHEXT - See below)

The program emulates the method by which cmd.exe resolves the path to a file. 

The program uses the PATH environment variable, prepended with the user's current directory to search for a match.

If -x  is not specified, the program will first attempt to match the file exactly as it was specified. (cmd != cmd.exe) If no match was found (or -a is specified), it will then use the PATHEXT environment variable and search for a file matching <program>.<extension>. (cmd == cmd.exe)

#### Example

Using command prompt:

	echo @echo Test1 > test.bat
	echo @echo Test2 > test.bat.bat
	
	which test
	-- Returns:
		[Current Folder]\test.bat

	which test.bat
	-- Returns:
		[Current Folder]\test.bat
	
	which -a test.bat
	-- Returns:
		[Current Folder]\test.bat
		[Current Folder]\test.bat.bat

	which -x test
	-- Returns:
		no test in ([PATH])

#### To Do

* Add code for the -a switch. Need to write a new function for iterating the PATH, etc.
* Use a list struct to allow the user to specify multiple executables to search for.
