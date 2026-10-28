*This project has been created as part of the 42 curriculum by cmyae.*

# ft_printf

## Description

`ft_printf` is a recreation of the C standard library's `printf()` function, built as a static library (`libftprintf.a`). The goal of the project is to understand and reimplement variadic functions in C, and to build well-structured, extensible code around C's format-string convention.

The mandatory part implements the following conversions:

| Conversion | Description |
|---|---|
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address, in hexadecimal |
| `%d`, `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x`, `%X` | Unsigned hexadecimal (lowercase / uppercase) |
| `%%` | Literal percent sign |

The bonus part adds support for flags, a minimum field width, and precision, following the general `printf` conversion grammar:

```
%[flags][width][.precision]conversion
```

### Which flags apply to which conversion

Not every flag has a defined effect on every conversion — this mirrors the real `printf` specification, and was verified against the system's own `printf` during development.

| Flag | `%c` | `%s` | `%p` | `%d` / `%i` | `%u` | `%x` / `%X` | `%%` |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| `-` (left-align) | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | — |
| `0` (zero-pad) | — | — | — | ✅ | ✅ | ✅ | — |
| `+` (force sign) | — | — | — | ✅ | — | — | — |
| ` ` (space for positive) | — | — | — | ✅ | — | — | — |
| `#` (alternate form) | — | — | — | — | — | ✅ | — |
| width | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | — |
| precision | — | ✅ (truncates) | — | ✅ (min digits) | ✅ (min digits) | ✅ (min digits) | — |

Flags with no defined effect on a conversion (e.g. `#` on `%c`, `+` on `%u`) are simply not applied — this matches real `printf`'s own behavior, where such combinations are non-standard and, in some cases, actively rejected by the compiler's own format-string checking.

### Override rules

Several flags interact with each other, and the later one doesn't always simply "add on top" of the earlier one:

- **`-` (left-align) overrides `0` (zero-pad).** When both are given, the field is space-padded on the right rather than zero-padded — zero-padding only makes sense when the content is right-justified.
- **An explicit precision overrides `0` for width-padding on numeric conversions.** The `0` flag stops affecting the *field width* padding when a precision is given, since precision already controls leading zeros on the digits themselves. The two paddings are independent: precision's zero-padding on the digits still applies even when width falls back to spaces.
- **`+` overrides a space flag when both are present**, regardless of which order they appear in the format string — the sign shown is always `+`, never a blank space, whenever `+` is present at all.
- **`#` has no effect when the hexadecimal value is `0`.** `%#x` on `0` prints `0`, not `0x0` — the prefix is only added when the value is non-zero.
- **Precision `0` combined with a value of `0` produces no digits at all.** `%.0d` on `0` prints nothing (an empty result) — this is a special case distinct from a non-zero value with precision `0`, which prints normally (precision is a minimum, not a truncation, for numeric conversions).
- **Numeric precision pads up, never truncates.** Unlike `%s`, where precision sets a *maximum* length (truncating longer strings), precision on `%d`/`%i`/`%u`/`%x`/`%X` only ever adds leading zeros when the value has *fewer* digits than the precision — it never removes digits from a value that already has more.

## Instructions

### Compilation

```sh
make        # builds the mandatory part -> libftprintf.a
make bonus  # builds the bonus part (flags, width, precision) -> libftprintf.a
make clean  # removes object files
make fclean # removes object files and the library
make re     # rebuilds from scratch
```

### Usage

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! You have %d new messages.\n", "world", 5);
    return (0);
}
```

Compile and link against the built library:

```sh
cc your_file.c -L. -lftprintf -I. -o your_program
```

## Resources

- `man 3 printf` — the reference for `printf`'s conversion specification and flag behavior
- [Tripouille/printfTester](https://github.com/Tripouille/printfTester) — a widely used community test suite for `ft_printf`, used throughout development to compare output and return values against the system's real `printf`
- [Chanmyae27/42](https://github.com/Chanmyae27/42) — this repository, containing the full 42 curriculum coursework including this project

### AI usage

AI (Claude, Anthropic) was used as a learning aid throughout this project, primarily for:

- Explaining C concepts directly relevant to the project — variadic functions and `va_list`/`va_arg` semantics, default argument promotion, and why `va_arg`'s type must match the type the caller actually passed
- Debugging: tracing specific bugs by hand (e.g. an off-by-one in format-string index advancement, an `INT_MIN` sign-overflow issue, an uninitialized-variable Norm violation, a use-after-free from freeing the wrong pointer, an out-of-bounds read on a malformed format spec) and verifying fixes by compiling and running them against the system's real `printf`, and in some cases under AddressSanitizer
- Verifying flag/edge-case behavior (e.g. `#` with a zero value, `+`/space priority, precision-vs-width zero-flag suppression) by compiling small test programs against the system's own `printf` rather than relying on assumption
- Checking Norm compliance with the actual `norminette` tool for a small number of specific functions during refactoring
- Architectural discussion for the bonus flag-parsing pipeline (splitting conversion logic into content-building and width/precision-formatting stages) and light scaffolding for a few specific helper functions

The core parsing logic, conversion handlers, and bonus flag/width/precision implementation were written and iterated on directly by the author; AI was not used to generate a complete solution to be copied in.

## Algorithm and data structure

### Format string parsing

`ft_printf` walks the format string one character at a time. Literal characters are written immediately. On encountering a `%` followed by another character, the format spec is parsed in three stages — flags, then an optional width, then an optional precision — before dispatching to a handler based on the final conversion character. The position where `%` was found is retained (in the flags struct) so that a malformed conversion spec — one that reaches the end of the string, or an unrecognized conversion character, without ever finding a valid conversion — can be printed back out literally instead of silently discarded or causing an out-of-bounds read.

### `t_flags` struct

A single struct carries the parsed state of one conversion spec — left-align, zero-pad, plus, space, and hash flags, the field width, the precision value and whether a precision was explicitly given at all (distinct from a precision of `0`), and the starting index of the current `%`. It is reset between conversions so that flags from one conversion never bleed into the next, or into literal text between conversions.

### Content-then-format pipeline (bonus)

For the mandatory conversions, output is written directly as it's computed — there is nothing to know in advance. For bonus, width, precision, and sign/prefix placement all require knowing the *final length* of the output before any padding decision can be made — so each conversion first builds its raw content (digits, a string, a sign or `0x` prefix) into a heap-allocated buffer, then a shared formatting step applies precision and width padding to that buffer, and only then is the result written to `stdout` in a single `write` call. This also keeps memory ownership simple: each function that allocates a buffer it doesn't need to return frees it before returning, and each function that returns a buffer hands ownership to its caller.

### Safe handling of `INT_MIN`

Negating a negative `int` directly can overflow when the value is `INT_MIN`, since its magnitude has no positive `int` representation. Signed values are widened to `long` before any negation, avoiding the overflow entirely, before being converted to `unsigned long` for digit extraction.
