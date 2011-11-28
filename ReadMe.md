## Which for Windows

#### Usage

	which [-a] program

If -a is specified, it will list all matches found. Otherwise, it will list the first available match.

The program uses the PATH environment variable, prepended with the user's current directory to search for a match.

If no extension is specified, it will use the PATHEXT environment variable.