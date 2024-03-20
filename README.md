Welcome to myshell.

Shells are a way for a user to interface with the kernel of an operating system. The concept of shells go back to ARPANET days when genius Louis Pouzin made RUNCOM, an interpreter that ran commands from a file[2]. The first significant shell was made back in 1979 by Stephen Bourne, with the intent of automating system administration tasks[2], which is the grandparent of the default shell on most linux distributions, suitably named "Bourne Again SHell".

A shell breaks up the input of a user into "tokens" divided by whitespace, and uses these to perform a range of activities such as:
	1. Executing built in commands
	2. Running external commands and programs
	3. Redirecting input and output to different files
	4. Running certain processes in background



Commands:
Built-in commands in the shell are as follows:

  dir:
    Lists all items in the currently directory.
    Can be given the path of a different directory and list the contents of that instead.

  cd:
    Moves to home directory
    Can move to any directory you want if given the path as an argument

  quit:
    Quits program

  pause:
    Halts program until 'Enter' key is pressed

  clr:
    Clears the terminal window

  environ:
    displays enviroment variables

I/O Redirection:
I/O Redirection is temporarily changing the input or output of a program from the command line to a file. This is very useful as it prevents us repeatedly having to type the same test cases for our code out when we change input, and we can also write the output of a program to a file if we'd like aswell.

  Input Redirection:
    "< filename"
    Example:
      python3 test.py < input.txt

  Output Redirection:
    "> filename"
    Example
      python3 test.py > output.txt
    This type of output redirection truncates file, and writes over whatever is in it.

    ">> filename"
    Example python3 test.py >> output.txt
    Example
      python3 test.py > output.txt
    This type of output redirection appends to file rather than truncating.

  Syntax can be mixed and matched as long as arrow is on left and desired file for redirection is on right

  The command "python3 < input.txt test.py > output.txt" is valid although I don't know why you would do this to be fair.


References:
[1]UNIX Shells by Example - Ellie Quigley
[2]Inventions of Louis Pouzin - Chantal Lebrument, Fabien Soyez
