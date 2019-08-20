#Assignment 1
Q1.c contains the code to revesrse the contents of a given file and write them into another file of the same name inside a directory named "Assignment"

Q2.c contains the code to check the permissions of the old file (contents of which were to be reversed ), the directory created by the first code and the new file created . other than that it also checks if the directory was created and if the contents in the new file are actually the reverse of the old file .

## Q1.c
mainly uses the following header files :

unistd.h

fcntl.h

stdlib.h

it uses only system calls to read contents of the given file from the end , chunk by chunk , reverse each chunk and write the reversed chunk onto the new file from beginning .

there is a progress meter which tells the percentage of file reversed .

the size of the chunk is taken to be 1% of the total file size .

to run :
```bash
gcc Q1.c
./a.out <filename>
```

## Q2.c
mainly uses the following header files :
unistd.h

fcntl.h

stdlib.h

sys/stat.h

sys/types.h

it uses only system calls to read contents of the newfile from the end , reverse them and compare them chunk by chunk to the contents of the old file from the beginning .

the size of chunk is taken to be 1% of the total file size .

the executable takes the following 3 inputs from the CLI :

path to new file , path to old file , path to the directory 

it also check the permissions 

to run 
```bash
gcc Q2.c
./a.out <path to newfile> <path to old file> <path to directory>
```

