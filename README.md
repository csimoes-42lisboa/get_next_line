*This project has been created as part of the 42 curriculum by csimoes.*

## Description

`get_next_line` is a 42 Common Core project that implements a function (`char *get_next_line(int fd)`) to read a file descriptor line by line, returning each line including its terminating `\n` (when present) up to `EOF`, or `NULL` on error or when no more data remains.

To avoid $\mathcal{O}(N^2)$ when reading long lines with small `BUFFER_SIZE` values (such as `BUFFER_SIZE=1`) that leads to timeout, this implementation tracks accumulated bytes with a static `t_stash` structure (`data`, `len`, and `cap`) using geometric capacity growth (`cap *= 2`).

## Instructions

### Compilation

Run `make` at the root of the repository:

```bash
make
```

Available Makefile rules:
* `make` / `make all`: builds the object files (`get_next_line.o`, `get_next_line_utils.o`).
* `make clean`: removes object files (`.o`).
* `make fclean`: removes object files and generated build artifacts.
* `make re`: rebuilds everything from scratch.

### Usage

Include `get_next_line.h` in your program and compile with `-D BUFFER_SIZE=<n>`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

## Resources

* 42 `get_next_line` subject and Norminette guidelines
* Dynamic array geometric capacity growth references (`cap *= 2`) for amortized linear copy complexity

### AI Usage

AI was used as a technical mentor throughout this project to:
* Compare choices between (`t_stash` geometric capacity growth vs. chunk linked lists) for long lines with `BUFFER_SIZE=1`.
* Structure modular helper functions and edge-case handling (`fd < 0`, `BUFFER_SIZE <= 0`, `EOF` without `\n`, empty lines, and memory cleanup) under Norminette rules.
* Draft and refine the `Makefile` and this `README.md`.

All code was reviewed, adapted, and verified by the student.

## Detailed Description of the Implementation

The project is organized across `get_next_line.h`, `get_next_line.c`, and `get_next_line_utils.c`:

* **State & Capacity Structure (`t_stash`):** Stores `char *data`, `size_t len`, and `size_t cap` in a `static` variable so unread bytes after `\n` persist across calls without re-scanning the entire buffer on every read.
* **Buffered Reading & Capacity Growth:** Reads up to `BUFFER_SIZE` bytes per `read` call and doubles `cap` (`cap *= 2`) only when incoming data exceeds available capacity, keeping total copy operations linear.
* **Line Extraction & Cleanup:** Allocates and returns the exact line up to and including `\n` (or remaining bytes at `EOF`), then shifts remaining bytes or resets and frees `t_stash` on `EOF`, error, or allocation failure.