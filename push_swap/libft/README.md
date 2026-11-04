*This project has been created as part of the 42 curriculum by <cmyae>.*
 
# Libft
 
## Description
 
Libft is a personal C library built from the ground up, reimplementing a
selection of standard C library functions and adding a set of custom
utility functions on top of them. The goal is to understand how
commonly-used libc functions work internally by writing them myself,
and to build a small toolbox of reusable functions (string handling,
memory manipulation, and linked lists) for use in later 42 projects.
 
The library is split into three parts:
 
- **Part 1 — Libc functions**: reimplementations of standard functions
  such as `strlen`, `memcpy`, `strchr`, `atoi`, etc., prefixed with `ft_`
  and matching the original prototypes and behavior as described in
  their man pages.
- **Part 2 — Additional functions**: functions not present in the libc
  (or present in a different form), such as `ft_split`, `ft_substr`,
  `ft_strjoin`, `ft_itoa`, and file-descriptor output helpers.
- **Part 3 — Linked list**: a minimal singly-linked list implementation
  (`t_list`) with functions to create, add to, iterate over, map, and
  free lists.

## Instructions
 
### Compilation
 
Clone the repository and run `make` from the root:
 
```bash
make
```
 
This compiles every source file with `-Wall -Wextra -Werror` and
archives the resulting object files into `libft.a` using `ar`.
 
### Available Makefile rules
 
| Rule      | Effect                                               |
|-----------|------------------------------------------------------|
| `all`     | Builds `libft.a` (default rule)                      |
| `clean`   | Removes all object files                             |
| `fclean`  | Removes object files and `libft.a`                   |
| `re`      | `fclean` followed by `all`                           |
 
### Using the library in another project
 
Copy the `libft` folder into your project, then compile and link
against it:
 
```bash
cc your_file.c -Ilibft -Llibft -lft -o your_program
```
 
Make sure `libft.h` is included wherever you use one of its functions:
 
```c
#include "libft.h"
```
 
## Library Overview
 
### Part 1 — Libc functions
 
Character classification (`ft_isalpha`, `ft_isdigit`, `ft_isalnum`,
`ft_isascii`, `ft_isprint`), memory functions (`ft_memset`, `ft_bzero`,
`ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`), string functions
(`ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`,
`ft_strncmp`, `ft_strnstr`), case conversion (`ft_toupper`,
`ft_tolower`), integer conversion (`ft_atoi`), and allocation helpers
(`ft_calloc`, `ft_strdup`).
 
### Part 2 — Additional functions
 
- `ft_substr` — extract a substring from a string.
- `ft_strjoin` — concatenate two strings into a newly allocated one.
- `ft_strtrim` — trim characters from the start and end of a string.
- `ft_split` — split a string into an array of strings on a delimiter.
- `ft_itoa` — convert an integer into a newly allocated string.
- `ft_strmapi` / `ft_striteri` — apply a function to each character of
  a string, either building a new string or modifying in place.
- `ft_putchar_fd` / `ft_putstr_fd` / `ft_putendl_fd` / `ft_putnbr_fd` —
  output helpers writing directly to a file descriptor.

### Part 3 — Linked list
 
A `t_list` node holds a `void *content` and a pointer to the `next`
node. Functions cover creation (`ft_lstnew`), insertion
(`ft_lstadd_front`, `ft_lstadd_back`), traversal (`ft_lstsize`,
`ft_lstlast`, `ft_lstiter`), transformation (`ft_lstmap`), and cleanup
(`ft_lstdelone`, `ft_lstclear`).
 
## Resources
 
- [The Linux man-pages project](https://man7.org/linux/man-pages/) —
  reference for the exact prototypes and behavior of each libc function
  being reimplemented.
- [BSD `<string.h>` man pages](https://man.openbsd.org/) — reference
  for `strlcpy`/`strlcat`, which are not part of glibc by default.
- 42 Norm documentation — for the coding style rules enforced across
  the project (no globals, static helper functions, function/line
  limits).

### Testing
 
Every function in this library was verified against two external
testers before submission, both run to a fully passing state:
 
- [Tripouille/libftTester](https://github.com/Tripouille/libftTester)
- [wxsonz/bro42](https://github.com/wxsonz/bro42) — a pair-programming,
  guidance and testing companion for the Libft subject, checking not
  just function correctness but also the Makefile, forbidden symbols,
  Norm, and README against the subject's own clauses.
To run them:
 
```bash
# libftTester
git clone https://github.com/Tripouille/libftTester.git
cp libftTester/* .          # or place the tester alongside libft.h and libft.a
make m                      # launch mandatory tests
make b                      # launch bonus tests, if applicable
make [function name]        # launch the test for a single function, e.g. make calloc
 
# bro42
git clone https://github.com/wxsonz/bro42.git ft_bro
cd ft_bro
./install.sh                # installs the `bro` command
cd ~/my_libft                # run from inside your libft repository
bro                          # run everything and open the dashboard
bro ft_split                 # test a single function, verbose
bro macro                    # build/Makefile/Norm/README checks only
```
 
`bro42` writes nothing into this repository — its reports and cache
live under `~/.cache/ft_bro/`, so `git status` stays clean.

### AI usage disclosure
 
An AI assistant (Claude, via claude.ai) was used throughout this
project in a Socratic/review capacity rather than to generate code:
 
- Reviewing already-written functions (e.g. `ft_strlcpy`, `ft_split`,
  `ft_fill`) to identify concrete bugs — such as a `size_t` unsigned
  underflow in a cleanup loop, a hidden side effect inside a
  `while (... && len++)` condition causing an infinite loop, and an
  unfilled `NULL` variable/parameter mismatch preventing compilation.
- Explaining the logic and edge cases required by function
  specifications (e.g. the `INT_MIN` overflow trap in `ft_itoa`, why
  `ft_memmove` needs directional copying for overlapping regions, why
  `ft_atoi` does not need `INT_MIN`/`INT_MAX` clamping per the man
  page's undefined-behavior clause) without providing ready-to-paste
  solutions.
All function logic was written and debugged by the author; AI was used
to check compiled output, point out bugs, and explain the reasoning
behind fixes rather than to supply implementations directly. 
