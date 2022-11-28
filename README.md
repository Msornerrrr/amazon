# School Projects: Amazon
- Email: hjiang86@usc.edu
- Name: Richard Jiang
- OS: linux (recommend)

## How to start
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

## How to run
we could run the program with default database
```
./amazon
```
or we could specify the input database
```
./amazon db_filename.txt
```

- AND
search products with keyword1 AND keyword2 AND keyword3 AND ...
```
ADD term1 term2 ...
```

- OR
search products with keyword1 OR keyword2 OR keyword3 OR ...
```
OR term1 term2 ...
```

- ADD
add desired products to specified user's cart
```
ADD username product_number
```

- VIEWCART
view cart info for specified user
```
VIEWCART username
```

- BUYCART
buy all products in the user's cart
```
BUYCART username
```

- QUIT
quit the program without saving all the changes to the database
```
QUIT
```
quit but override the old db file with new changes
```
QUIT overriude
```
quit but save changes to db to a new file
```
QUIT new_db_filename.txt
```