# School Projects: Amazon
- Email: hjiang86@usc.edu
- Name: Richard Jiang
- OS: linux (recommend)

## How to run
- First, compile the code (three options)
``` powershell
make
make all
make amazon
```

- Run with given database.txt file (Note: path to .txt file must be provided as second argument)
``` powershell
./amazon db/database.txt 
```

- use valgrind to check memory leak
``` powershell
make valgrind
```

- clean object and executable files
``` 
make clean
```
