# CSCI-104 Homework 2
Email: hjiang86@usc.edu
Name: Richard Jiang
Section: 29930R 2:00 - 3:20 pm
OS: linux (recommend)

## How to run
First, compile the code (three options)
``` powershell
make
make all
make amazon
```

Or, you could also compile individual object file if you like
```
make file.o
```

Note: need to have all object.o available to produce executable

Run with given database.txt file (Note: path to .txt file must be provided as second argument)
``` powershell
./amazon database.txt 
```

use valgrind to check memory leak
``` powershell
valgrind --tool=memcheck --leak-check=yes ./amazon
```

clean object and executable files
``` 
make clean
```