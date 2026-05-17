*This project has been created as part of the 42 curriculum by ecakiray.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor.

The goal of this project is to understand how file descriptors, dynamic memory allocation, the `read()` system call, and static variables work together. Each call to `get_next_line(int fd)` returns the next available line from the given file descriptor until the end of the file is reached or an error occurs.

The returned line includes the newline character `\n` when it exists in the file. If the file ends without a final newline, the last line is still returned correctly.

## Prototype

```c
char *get_next_line(int fd);
```

## Submitted Files

Mandatory files:

```text
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

Bonus files:

```text
get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h
```
## Instructions

Compile the mandatory project with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Compile the bonus project with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

`BUFFER_SIZE` can be changed during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line_bonus.c get_next_line_utils_bonus.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line_bonus.c get_next_line_utils_bonus.c
```

The project also provides a default value for `BUFFER_SIZE` in `get_next_line.h`, so it can be compiled without defining it manually:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c
```

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

## Algorithm Explanation

### Mandatory Algorithm

This implementation uses a static character array named `remain`:

```c
static char remain[BUFFER_SIZE + 1];
```

The purpose of this static variable is to keep unread data between different calls to `get_next_line`. Since a call to `read()` may read more characters than the current line needs, the extra characters must not be lost. They are stored in `remain` and used during the next function call.

The algorithm works as follows:

1. When `get_next_line()` is called, it first checks whether `remain` already contains data from a previous read.
2. If `remain` contains a newline character, the function extracts and returns the line up to and including `\n`.
3. If there is no newline, the content of `remain` is appended to the current line, and another `read()` call is made.
4. The function keeps reading until it finds a newline, reaches the end of the file, or encounters an error.
5. When a newline is found, everything after that newline stays inside `remain` for the next call.
6. When the end of the file is reached, the final line is returned if it contains data. After that, the function returns `NULL`.

This approach avoids reading the whole file at once. It only reads as much as needed to return the next line, which is the expected behavior for this project.


### Bonus Algorithm

The bonus version keeps the same general reading logic as the mandatory version, but it stores a separate `remain` buffer for each file descriptor:

```c
static char remain[OPEN_MAX][BUFFER_SIZE + 1];
```

This is still only one static variable, because the static object is the two-dimensional array `remain`. The first index represents the file descriptor, and the second index stores the unread characters for that file descriptor.

For example, `remain[3]` stores the leftover data for file descriptor `3`, while `remain[4]` stores the leftover data for file descriptor `4`. This makes it possible to call `get_next_line()` on different file descriptors in alternating order without mixing their reading states.

The bonus algorithm works as follows:

1. `get_next_line(fd)` checks whether `fd` is valid and smaller than `OPEN_MAX`.
2. It uses `remain[fd]` instead of a single shared `remain` buffer.
3. If `remain[fd]` already contains data from a previous read, that data is processed first.
4. If no newline is found, the function reads more data from the same `fd` into `remain[fd]`.
5. When a newline is found, the returned line is built and the extra unread data stays in `remain[fd]`.
6. Other file descriptors keep their own remaining data in their own slots.

This allows the bonus version to manage multiple file descriptors at the same time while preserving the mandatory implementation style.

## Function Overview

### `get_next_line`

Main function of the project. It returns the next line from the given file descriptor.

### `get_next_line_bonus`

Bonus version of the main function. It uses `remain[fd]` so each file descriptor has its own stored reading state.

### `use_remain`

Processes the current content of the static `remain` buffer. It separates the part that belongs to the returned line from the part that must be kept for the next call.

### `read_part`

Reads new data from the file descriptor into `remain` and sends it to `use_remain` for processing.

### `till_nl`

Splits a string around the first newline character. The part up to the newline is used for the current line, while the rest is stored as remaining data.

### `join_line`

Creates a new dynamically allocated string by joining the current line with newly read content. The old line is freed to prevent memory leaks.

## Technical Choices

- A static array is used to preserve unread data between function calls.
- `read()` is called with `BUFFER_SIZE`, which allows the evaluator to test different buffer sizes.
- Dynamic memory is used for returned lines because each line can have a different length.
- Helper functions are kept in `get_next_line_utils.c` to keep the main file easier to read.

## Limitations

The mandatory version uses one static buffer for one reading state. It is designed for the mandatory part of the project.

The bonus version uses `OPEN_MAX` to create one storage slot per file descriptor. File descriptors outside this range are considered invalid.

The behavior is undefined if the file is modified between calls before `read()` reaches the end of the file. Reading binary files is also outside the expected behavior of the project.

## Resources

- `man 2 read`
- `man 3 malloc`
- `man 3 free`
- 42 subject: Get Next Line
- C static variables documentation and examples
- File descriptor tutorials in C

## AI Usage

AI was used to help organize this README, explain the mandatory and bonus algorithms clearly, and review edge cases related to static variables and multiple file descriptors.

## Testing
The project was tested using:
- libft-unit-test by francinette: https://github.com/xicodomingues/francinette

Special thanks to my all 42 Heilbronn colleagues.

Made by ecakiray: ecakiray@student.42heilbronn.de | LinkedIn: [ecakiray](https://www.linkedin.com/in/eraycakiray/)
