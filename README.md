**Overview**

The Get Next Line project implements a function that reads a line from a file descriptor (FD) one line at a time. It’s designed to efficiently handle file reading, returning the next line each time it is called.

**Features**

Efficient line-by-line reading from files.
Handles multiple file descriptors independently (bonus version).
Optimized to minimize unnecessary memory allocations and prevent leaks.
How to Use

Clone the repository:
```
git clone https://github.com/daniek1010/get_next_line.git && cd get_next_line
```

Compile the source files with your own main.c and use the get_next_line function:

````
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl_test
````

Run the executable:

````
./gnl_test
````
