*This project has been created as part of the 42 curriculum by cmyae.*

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file descriptor:

```c
char *get_next_line(int fd);
```

Calling it repeatedly in a loop reads the whole file, one line per call. Each returned line includes its terminating `\n`, except the last line of a file that does not end with a newline. When there is nothing left to read, or an error occurs, it returns `NULL`. It works on regular files as well as on standard input and other file descriptors such as pipes.

The project teaches how to keep state between calls (`static` variables), how `read()` really behaves (it returns arbitrary chunks that do not respect line boundaries), and how to manage heap memory without leaks.

Allowed external functions: `read`, `malloc`, `free`. `libft`, `lseek` and global variables are forbidden.

### Files

| Part | Files |
| --- | --- |
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` |
| Bonus | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` |

### Bonus

The bonus version uses a single `static` variable and can read from several file descriptors at the same time. You can alternate calls between fd 3, 4 and 5 and each one keeps its own reading position and never returns a line from another.

## Instructions

The subject does not require a Makefile for this project, so the files are compiled directly. The size of the `read()` buffer is set at compile time with `-D BUFFER_SIZE=n`. If the flag is omitted, a default of `42` is used.

**Mandatory**

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

**Bonus**

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

`main.c` is your own test program. A minimal one:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Reading from standard input works the same way with `fd = 0`.

The returned line is allocated with `malloc`, so the caller must `free` it.

## Algorithm

### The problem

`read(fd, buf, BUFFER_SIZE)` returns up to `BUFFER_SIZE` bytes with no regard for lines. One call can return half a line, exactly one line, or several lines and the start of another. Whatever was read past the end of the requested line must be kept for the next call. That is why the function needs a `static` variable.

### Data structure: a linked list of chunks

Every `read()` result is stored as a node and appended to a list:

```c
typedef struct s_node
{
	char			*content;   /* the bytes of one read() */
	size_t			len;        /* how many bytes are valid */
	struct s_node	*next;
}	t_node;
```

The `static` pointer holds the head of this list. It contains only what was read from the file descriptor but not yet returned.

### Steps of one call

1. If the list already contains a `\n` (left over from the previous call), skip reading.
2. Otherwise, repeat: allocate a buffer, `read()` into it, wrap it in a node, append it to the list. Stop as soon as the newly read chunk contains a `\n`, or when `read()` returns 0 (end of file) or a negative value (error).
3. Measure the length of the line: the number of bytes up to and including the first `\n`, or the whole list if there is none.
4. Allocate `length + 1` bytes and copy the line out across the nodes.
5. Clean the list: free every node that was fully consumed. If the node holding the `\n` has bytes after it, shift them to the front of that node and keep it as the new head of the list. The list now holds only the leftover.

### Why a linked list instead of one flat string

The usual first approach keeps the leftover in a single string and joins every new chunk onto it. Each join allocates a new string and copies everything read so far. With a long line and a small `BUFFER_SIZE`, the same bytes are copied again and again, so the total work grows with the square of the line length (O(n²)). With `BUFFER_SIZE=1` and a line of 10,000 characters that already means about 10,000 allocations and tens of millions of byte copies, which is slow enough to time out under a tester that wraps the program in `valgrind`.

With a linked list:

- **Appending is O(1).** A node is linked onto the end and nothing already read is copied again. The tail pointer (`last`) avoids walking the list to find the end.
- **The newline check is cheap.** Only the newest chunk is scanned for `\n` after each `read()`, never the whole accumulated list, so scanning does not grow with line length.
- **Each byte is copied once** into the final line, when the line is assembled. Total work is linear in the length of the line.

Measured at `BUFFER_SIZE=1`, running time scales roughly linearly with line size (a 10x longer line takes about 10x longer), where the flat-string version scaled much worse.

The trade-off is one `malloc` per `read()` call for the node, plus one for its buffer, in exchange for never recopying earlier data.

### Invariants worth knowing

- After a call, the list holds **at most one node**: the tail of the node that contained the `\n`. This is because reading stops the moment a chunk containing `\n` arrives, so no node can exist after it.
- Because of this, the tail pointer can be a plain local variable of each call. At the start of a call the list has at most one node, so finding its tail is trivial.
- The check "does the list already contain a `\n`?" at the start of the call avoids a needless `read()`. This matters for standard input and pipes, where a `read()` with no data available would block even though a complete line was already waiting.

### Edge cases

| Case | Behaviour |
| --- | --- |
| Empty file | Returns `NULL` immediately |
| Last line without a trailing `\n` | Returned as is, without a `\n`; the next call returns `NULL` |
| File that is only `\n` characters | One call per `\n`, each returning `"\n"` |
| `read()` returns a negative value | All stored data is freed and `NULL` is returned |
| `malloc` failure | Everything allocated so far is freed and `NULL` is returned |
| Invalid fd (`fd < 0`) or `BUFFER_SIZE <= 0` | Returns `NULL` |
| `BUFFER_SIZE` of 1 or very large (for example 10,000,000) | Works in both cases: the buffer size only affects how many `read()` calls are made and how large each chunk is |

## Bonus: multiple file descriptors

The mandatory version keeps one list in one `static` pointer, so it can only follow one file descriptor. The bonus keeps a **list of per-fd entries** behind a single `static` pointer:

```c
typedef struct s_fd_node
{
	int					fd;
	t_node				*node;   /* head of this fd's chunk list */
	t_node				*last;   /* tail of this fd's chunk list */
	struct s_fd_node	*next;
}	t_fd_node;
```

- At the start of each call, the entry for this fd is looked up. If it does not exist, a new one is created and linked at the head of the list.
- The rest of the algorithm is the same as the mandatory one, but it operates on that entry's `node` and `last` instead of on a single global-like list.
- When an fd has nothing left (end of file, error, or after its last line has been returned), its entry and any remaining chunks are freed and unlinked, so no memory is left behind and a reused fd number never inherits stale data.

Why a list of entries rather than an array such as `static t_node *stash[OPEN_MAX]`? The list needs no assumption about the largest possible fd number, uses memory only for fds that are actually in use, and reuses the same linked-list technique as the chunks. The cost is a lookup that walks the entries, which is negligible for a realistic number of open files.

## Testing

- Compiled with `-Wall -Wextra -Werror` both with and without `-D BUFFER_SIZE`.
- Tested with the community `gnlTester` suite.
- Own tests: byte-for-byte comparison of the returned lines against the original file for several `BUFFER_SIZE` values (1, 2, 5, 42, 9999 and 10,000,000), standard input through a pipe, and for the bonus, interleaved reads from three files of different lengths. Run with AddressSanitizer and LeakSanitizer to check for invalid memory access and leaks.

## Resources

### References

- `man 2 read`, `man 3 malloc`, `man 3 free`: behaviour of `read()` (return values 0 and -1, partial reads) and of the allocation functions.
- Documentation on `static` variables in C: storage duration, and why a `static` local keeps its value between calls without being a global variable.
- Documentation on file descriptors: standard input is fd 0, and descriptors can refer to pipes and terminals as well as regular files.
- The 42 Norm and the project subject (`en_subject.pdf`).
- `gnlTester`: community test suite used for checking the mandatory and bonus parts.

### How AI was used

AI (Claude) was used as a learning and review aid, following the AI guidelines of the subject. It was not used to generate the project's implementation.

- **Concepts and design discussion:** understanding what a `static` variable does here, comparing possible strategies (a leftover string versus a linked list of chunks versus a rotating buffer), and, for the bonus, comparing a fixed-size array indexed by fd with a dynamic list of per-fd entries.
- **Code review and debugging:** pointing out bugs in work-in-progress code, such as a NULL dereference on the first call, a `free` placed where it released memory still in use, freeing an advanced pointer instead of the original allocation, a wrong `malloc` size, signed/unsigned handling of the `read()` return value, and leaks on early-return paths. The fixes were written by the author.
- **Performance analysis:** identifying why a flat-string approach times out with a small `BUFFER_SIZE` on a very long line (the O(n²) re-copying and re-scanning described above), which led to the switch to a linked list.
- **Testing:** suggesting test cases and running sanitizer-based checks on submitted code.
- **Norm planning:** helping budget the number of functions and lines per file for the bonus.
- **Documentation:** this README was drafted with AI assistance from the project's code, then reviewed by the author.

All code was reviewed, understood and is explainable by the author.
