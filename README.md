# 42 - GET_NEXT_LINE PROJECT

### Introduction
This project will not only allow you to add a very convenient function to your collection, but it will also allow you to learn a highly interesting new concept in C programming which are static variables.

## Mandatory Part
Write a function which returns a line read from a file descriptor.

### Technical Considerations
* Calling your function get_next_line in a loop will then allow you to read the text available on the file descriptor one line at a time until the end of it
* Your function should return the line that has just been read. If there is nothing else to read or if an error has occurred it should return NULL
* Make sure that your function behaves well when it reads from a file and when it reads from the standard input
* libft is not allowed for this project. You must add a get_next_line_utils.c file which will contain the functions that are needed for your get_next_line to work
* Your program must compile with the flag -D BUFFER_SIZE=xx which will be used as the buffer size for the read calls in your get_next_line
* The program will be compiled in this way: gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \<files\>.c.
* Your read must use the BUFFER_SIZE defined during compilation to read from a file or from stdin
* lseek is not an allowed function. File reading must be done only once
* We consider that get_next_line has undefined behavior if, between two calls, the same file descriptor switches to a different file before reading everything from the first fd
* Finally we consider that get_next_line has undefined behavior when reading from a binary file. However, if you wish, you can make this behavior coherent
* Global variables are forbidden
* The returned line should include the ’\n’, except if you have reached the end of file and there is no ’\n’

## Bonus Part
* To succeed get_next_line with a single static variable
* To be able to manage multiple file descriptors with your get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors
