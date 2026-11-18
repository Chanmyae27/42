*This project has been created as part of the 42 curriculum by kthu, cmyae.*

# push_swap

## Description

`push_swap` sorts a list of unique integers using two stacks (`a` and `b`) and a
restricted set of operations. The program prints the sequence of operations that
leaves stack `a` sorted in ascending order (smallest value on top) with `b` empty.

The goal of the project is to experience **algorithmic complexity** concretely:
the same input can take a few dozen or tens of thousands of operations depending
on the algorithm. The program therefore embeds four strategies and can pick one
automatically from the measured **disorder** of the input.

| Strategy | Flag | Class (in number of generated operations) |
|---|---|---|
| Simple (selection sort) | `--simple` | O(n²) |
| Medium (chunk sort) | `--medium` | O(n√n) |
| Complex (LSD radix sort on ranks) | `--complex` | O(n log n) |
| Adaptive (default) | `--adaptive` | O(n²) / O(n√n) / O(n log n) depending on disorder |

### Allowed operations

`sa sb ss` (swap), `pa pb` (push), `ra rb rr` (rotate), `rra rrb rrr` (reverse rotate).

## Instructions

### Compilation

```sh
make        # builds libft, then push_swap (cc -Wall -Wextra -Werror, no relink)
make clean  # removes object files
make fclean # removes objects and the binary
make re     # fclean + all
```

### Execution

```sh
./push_swap [strategy] [--bench] <integers...>
```

- Integers can be given as separate arguments or inside a quoted string
  (`./push_swap "3 2 1"`). The first value is the top of stack `a`.
- `strategy` is one of `--simple`, `--medium`, `--complex`, `--adaptive`
  (default: `--adaptive`).
- `--bench` prints a statistics report on **stderr** (see below).
- No arguments: nothing is printed.
- Invalid input (non-integer, out of `int` range, duplicates, unknown flag,
  several strategy flags) prints `Error` on **stderr**.

### Examples

```sh
$ ./push_swap 2 1 3 6 5 8
$ ./push_swap --complex 4 67 3 87 23 | wc -l
$ ./push_swap --bench $(shuf -i 0-9999 -n 500) 2> bench.txt | wc -l
$ ./push_swap 0 one 2 3
Error
```

### Benchmark output

With `--bench`, the following goes to stderr:

```
[bench] disorder: 40.00%
[bench] strategy: Adaptive / O(n*sqrt(n))
[bench] total_ops: 6
[bench] sa:0 sb:0 ss:0 pa:2 pb:2 ra:1 rb:0 rr:1 rra:0 rrb:0 rrr:0
```

The counts are computed from the **final** operation list (after optimization),
so they match exactly what is printed on stdout.

## Project structure

```
includes/push_swap.h     types and prototypes
src/main.c               program flow
src/parse/               flag parsing, argument parsing, validation, ranks
src/stack.c              ring-buffer stack primitives
src/operations/          op_basics (swap/push/rotate), op_log (growable log),
                         optimize (peephole pass), bench (report)
src/exec.c               single entry point that applies + logs an operation
src/disorder.c           disorder metric
src/strategy.c           strategy selection and names/complexity labels
src/sort/                tiny, simple, medium, complex sorts and helpers
libft/                   libft (with ft_printf)
```

### Program flow

1. `parse_flags`: read the strategy selector and `--bench`.
2. `parse_values`: split arguments, validate integers (overflow, duplicates),
   then **normalize to ranks** `0..n-1`.
3. `compute_disorder` on the initial stack, before any move.
4. `sort_stack`: nothing if already sorted, `sort_tiny` for ≤ 3 elements,
   otherwise the selected strategy.
5. `optimize_log`: peephole pass over the recorded operations.
6. Output the operations on stdout and, with `--bench`, the report on stderr.

## Data structures

- **Stacks:** each stack is an `int` array used as a **ring buffer** with `head`,
  `size` and `cap` (capacity n for both stacks, since all values can end up in
  one of them). Element `i` from the top lives at `(head + i) % cap`. Push, pop,
  rotate and reverse rotate only move `head` and/or write one value, so every
  operation is **O(1)** with a single allocation per stack.
- **Operation log:** a growable `unsigned char` array (capacity doubles when
  full). Every algorithm calls `exec_op`, the only function that changes the
  stacks, so the stacks and the log can never go out of sync.
- **Ranks:** input values are replaced by their rank (number of smaller values).
  Algorithms therefore only work on `0..n-1`, which makes radix and chunk logic
  independent of the actual values (negatives, `INT_MIN`, `INT_MAX`, gaps).
  Ranks are computed in O(n²), once, at start-up.

## Disorder metric

As required, disorder is the proportion of inverted pairs in the initial stack:

```
disorder = (# pairs i<j with a[i] > a[j]) / (n(n-1)/2)     in [0, 1]
```

It is 0 for a sorted stack and 1 for a reversed one. For a uniformly random
permutation its expected value is 0.5, because each pair is inverted with
probability 1/2. It is computed in O(n²) before any operation.

## Algorithms and justification

All complexities are measured in **number of push_swap operations generated**.

### Simple: selection sort, O(n²)

While `a` has more than 3 elements: find the minimum, rotate it to the top using
the cheaper direction (`ra` or `rra`, at most n/2 moves), `pb`. Sort the last 3
elements directly, then `pa` everything back (pushing the minima back in
decreasing order leaves `a` ascending).

- **Time:** n − 3 iterations of at most n/2 + 1 operations, plus n − 3 `pa`,
  so ≤ n²/2 + O(n) = **O(n²)**.
- **Space:** O(n) (the two stacks), O(1) extra.
- **Why:** it is easy to reason about and defend, and it is the baseline the
  other strategies are compared against.

### Medium: chunk sort, O(n√n)

Ranks are split into ranges ("chunks") of size `c = 1.4·⌊√n⌋`. Elements are
pushed to `b` chunk by chunk: while the top of `a` belongs to the current range
(`rank < pushed + c`) it is pushed with `pb`; smaller ranks (the older part of
the range) are additionally rotated to the bottom of `b` with `rb`; otherwise
`ra` skips it. Then the largest element of `b` is repeatedly rotated to the top
(cheaper direction) and pushed back with `pa`.

- **Time, push phase:** there are about n/c = O(√n) chunks, each needing at most
  one pass over `a` (≤ n rotations), so O(n√n).
- **Time, return phase:** `b` is kept roughly banded by rank (recent chunks near
  the top), so the maximum is always within O(c) = O(√n) positions of an end;
  n extractions × O(√n) = O(n√n).
- **Space:** O(n) for the stacks, O(1) extra.
- **Why:** chunk sorting keeps rotations short in both phases. The factor 1.4 is
  a tuning constant (it does not change the complexity class); \<describe how
  you chose it, e.g. the values you tested and the operation counts\>.

### Complex: LSD radix sort on ranks, O(n log n)

For each bit from 0 to ⌈log₂ n⌉ − 1: go through the whole of `a`; if the bit of
the rank is 1, `ra`, otherwise `pb`; then `pa` everything back. The pass is
stable, so after the last bit `a` is sorted. The loop stops early when `a` is
already sorted.

- **Time:** ⌈log₂ n⌉ passes of at most n (`ra`/`pb`) + n (`pa`) operations
  = **O(n log n)**; the number of operations is almost independent of the input
  order.
- **Space:** O(n) for the stacks, O(1) extra.
- **Why:** radix on ranks is short, deterministic, and has a guaranteed bound.
  It is the safest strategy for strongly disordered inputs.

### Tiny inputs

`sort_tiny` sorts 2 or 3 elements with at most 2 operations (it places the
maximum at the bottom, then swaps if needed). Already-sorted input prints nothing.

### Adaptive strategy

| Measured disorder | Method used | Class |
|---|---|---|
| < 0.2 | Simple (selection sort) | O(n²) |
| 0.2 ≤ d < 0.5 | Medium (chunk sort) | O(n√n) |
| ≥ 0.5 | Complex (radix sort) | O(n log n) |

- **Thresholds (0.2 / 0.5):** these are the values given by the subject. The
  0.5 limit has a natural meaning: it is the expected disorder of a random
  permutation, so anything at or above it is treated as the general (random or
  worse) case and gets the strategy with the best worst-case guarantee. Below it
  the input is partially ordered and the cheaper-to-run chunk method is used;
  below 0.2 the input is almost sorted and the simple method is enough.
- **Time bound:** the cost is the cost of the selected method, so the adaptive
  strategy is O(n²) in the low regime, O(n√n) in the medium regime and
  O(n log n) in the high regime. The disorder computation adds O(n²) CPU work
  but zero operations.
- **Space:** O(n), same as each method.
- **Selector flags** bypass the choice: `--simple`, `--medium` and `--complex`
  force a method for any input size and disorder.

### Operation optimization (peephole pass)

After sorting, the log is scanned once with a stack-like reduction:

- adjacent inverse pairs cancel (`ra`+`rra`, `rb`+`rrb`, `pa`+`pb`, `sa`+`sa`, ...);
- adjacent `ra`+`rb` become `rr`, `rra`+`rrb` become `rrr`, `sa`+`sb` become `ss`
  (in either order).

Because it runs on the log (not while sorting), a cancellation can cascade, and
the statistics are recomputed from the reduced log.

## Performance

Measured with a Python simulator of the operations as checker, 30 random
inputs per cell (values in a wide range, no duplicates). The simulator verified
that stack `a` was sorted and `b` empty for every run.

| Strategy | n = 100 (avg / worst) | n = 500 (avg / worst) |
|---|---|---|
| `--adaptive` (default) | 748 / 1014 | 5886 / 6742 |
| `--simple` | 1468 / 1706 | 32299 / 34168 |
| `--medium` | 549 / 578 | 4903 / 5129 |
| `--complex` | 1003 / 1016 | 6729 / 6744 |

Subject targets: for 100 numbers, under 2000 (pass) / 1500 (good) / 700
(excellent); for 500 numbers, under 12000 / 8000 / 5500. The O(n²) strategy is
expected to exceed the 500-number thresholds when forced with `--simple`; the
targets apply to the default behavior.

## Testing

```sh
# Correctness with the provided checker
ARG=$(shuf -i 0-9999 -n 100 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG

# Operation count
./push_swap $(shuf -i 0-9999 -n 500) | wc -l

# Errors
./push_swap 0 one 2 3          # Error
./push_swap 3 2 3              # Error
./push_swap 2147483648         # Error

# Memory
valgrind --leak-check=full ./push_swap $ARG
```

## Contributions

- **cmyae:** \<parsing and validation, stack and
  operation layer, benchmark output, optimizing\>
- **kthu:** \<sorting strategies, sorting operations, adaptive
  selection, tests\>

## Resources

### References

- Subject: *push_swap* (42), version 1.2.
- Big-O notation and algorithmic complexity: <https://en.wikipedia.org/wiki/Big_O_notation>
- Radix sort: <https://en.wikipedia.org/wiki/Radix_sort>
- Selection sort: <https://en.wikipedia.org/wiki/Selection_sort>
- Circular buffer (ring buffer): <https://en.wikipedia.org/wiki/Circular_buffer>
- Community write-ups on push_swap strategies (chunk/radix approaches), used for
  ideas only and re-implemented and tested by us.

### Use of AI

An AI assistant (Claude) was used for:

- **Planning:** discussing the program architecture, the choice between a linked
  list and an array, and a step-by-step implementation order.
- **Design review:** suggesting the ring-buffer stack layout, a growable
  operation log, rank normalization, and the idea of a peephole optimization
  pass.
- **Code review:** reviewing parsing/validation code and pointing out bugs,
  Norm issues and missing prototypes.
- **Documentation:** drafting this README.

All generated suggestions were read, tested (including with a checker and
random inputs) and are understood by both learners; the sorting algorithms and
the code in `src/` were written and are defended by us.
