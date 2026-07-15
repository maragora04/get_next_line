*This project has been created as part of the 42 curriculum by mamendes.*

---

# get_next_line

## Description

`get_next_line` is a project from the 42 school curriculum that challenges you to implement a C function capable of reading a single line at a time from a file descriptor. Each successive call to `get_next_line` returns the next line from the file, and the function works correctly regardless of the buffer size used during reading.

**Goal:** Implement the following function:

```c
char *get_next_line(int fd);
```

The function reads from the file descriptor `fd` and returns a heap-allocated string containing the next line (including the terminating `\n` if one exists). It returns `NULL` on end-of-file or on error.

**Bonus:** The bonus part extends the implementation to handle multiple file descriptors simultaneously — interleaved calls across different `fd` values each maintain their own independent reading state.

---

## Algorithm

### Overview

The core challenge of `get_next_line` is that a single `read()` call may fetch more bytes than needed (overshooting a `\n`), or fewer (not reaching the next `\n` yet). The solution requires a persistent buffer that survives across function calls — hence the use of a `static` variable.

### Step-by-step logic

```
+-----------------------------------------+
          |           get_next_line(fd)             |
          +-------------------+---------------------+
                              |
               [Does Static Buffer have data?]
                /                         \
             YES                           NO
             /                               \

+-------------v-------------+            +------v------+
| Extracted with beeline()  |            | read() new  |
|   and checked for '\n'    |            |    chunk    |
+-------------+-------------+            +------+------+
|                                 |
[Found '\n'?]                     [Join & clean]
/         \                             |
YES           NO                     [Found '\n'?]
/               \                     /

+---v----+       +----v-------------------v-+       +-v----+
| Return |       | Call read_and_join()     |       | Return|
|  line  |       | until '\n' or EOF is hit |       | line |
+--------+       +--------------------------+       +------+
```
The algorithm is divided into logical, modular components to ensure dry and clean execution:

### 1. Persistent Buffer & Shifting Strategy
Instead of re-allocating or creating complex circular queues, we maintain a single static string array `static char buffer[BUFFER_SIZE + 1]`. 
* **`newlinebuf`**: This helper function processes the buffer once a line segment is extracted. It locates the newline character, shifts all trailing characters to the front of the array (at index `0`), and null-terminates the remaining indices to clear out processed data. This guarantees that no leftover garbage is carried over to subsequent calls.

### 2. Precise Allocation via Custom Joining
* **`line_size`**: Determines the number of bytes up to (and including) the first `\\n` or `\\0`.
* **`ft_linejoin`**: A custom allocation and concatenation function. It computes the exact required space for the new string using `line_size`, copies the existing line plus the safe chunk from the buffer, and frees the previously allocated line to prevent memory leaks.

### 3. State Management with a Flag Link
To coordinate communication between the core loop in `get_next_line` and the system reading helper `read_and_join`, we pass a control variable `flag` by reference.
* `flag = 0`: Normal iteration; continue looking for a line or reading more bytes.
* `flag = 1`: Successfully hit EOF or a newline; break the loop and return the accumulated string.
* `flag = 2`: Read error (`bytesread < 0`) or critical allocation failure; completely clear the static buffer, free resources, and safely abort.

---

### Helper functions

| Function | Role |
|---|---|
| `line_size(buf)` | Returns the length of `buf` up to and including the first `\n` (or until `\0`) |
| `ft_linejoin(s1, s2)` | Allocates and returns `s1 + s2` (up to `\n`), then frees `s1` |
| `isnewline(s)` | Returns a pointer to the first `\n` in `s`, or `NULL` |
| `newlinebuf(line)` | Shifts everything after the first `\n` to the front of the buffer; zeros the rest. Returns `1` if a `\n` was found, `0` otherwise |
| `beeline(line, buf)` | Joins the existing buffer into `line`, calls `newlinebuf`, and returns the line if it contains a `\n` |

### Why this algorithm?

**Static buffer with in-place shift** was chosen for the following reasons:

- **Correctness across buffer sizes:** Since `BUFFER_SIZE` can be anything from 1 to very large values, the algorithm must handle partial reads and over-reads uniformly. The static buffer acts as a "leftover" store between calls without requiring dynamic memory for the buffer itself.

- **No dynamic memory for the buffer:** The buffer is stack-allocated as a `static` array. Only the returned `line` string is heap-allocated, keeping allocations minimal and well-defined.

- **Single-pass design:** The loop reads, joins, and checks for `\n` in one tight cycle. There is no second scan of already-processed data.

- **Bonus extension is natural:** For the multi-fd bonus, the static buffer becomes a 2D array indexed by `fd` (`buffer[FOPEN_MAX][BUFFER_SIZE + 1]`). Each file descriptor gets its own independent slot — zero changes to the algorithm logic are needed.

- **`newlinebuf` over memmove:** Rather than calling `memmove`, `newlinebuf` performs an in-place left-shift by scanning for `\n` and copying subsequent bytes to the start. This is explicit and easy to audit for correctness.

### Complexity

- **Time:** O(n) per call, where n is the number of bytes up to the next `\n`.
- **Space:** O(BUFFER_SIZE) for the static buffer + O(line length) for the returned heap string.

---

## Instructions

### Files

```
get_next_line/
├── get_next_line.c           # Main function (single fd)
├── get_next_line.h           # Header
├── get_next_line_utils.c     # Helper functions
├── get_next_line_bonus.c          # Main function (multiple fds)
├── get_next_line_bonus.h          # Header
└── get_next_line_utils_bonus.c    # Helper functions
```

### Compilation

You must pass `-D BUFFER_SIZE=<n>` to set the read buffer size. For example:

**Standard version (single fd):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

**Bonus version (multiple fds):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c -o gnl_bonus
```

> If `BUFFER_SIZE` is not specified, the default value defined in the header will be used.

### Using `get_next_line` in your own project

Include the relevant files and header in your project, then call the function as follows:

```c
#include "get_next_line.h"

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *str;
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close(fd);
	return 0;
}
```

Compile with:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 your_main.c get_next_line.c get_next_line_utils.c
```

> **Important:** Always `free()` the string returned by `get_next_line` after use to avoid memory leaks.

### Notes

- `BUFFER_SIZE` can be any positive integer. The function must work correctly for all values.
- The function is safe to call on `stdin` (fd = 0).
- The bonus version supports up to `FOPEN_MAX` simultaneously open file descriptors.
- Mixing calls between the standard and bonus versions in the same project is not intended.

---

## Resources

### Documentation & references

- [POSIX `read()` man page](https://man7.org/linux/man-pages/man2/read.2.html) — essential reference for the underlying system call
- [POSIX `open()` man page](https://man7.org/linux/man-pages/man2/open.2.html) — file descriptor handling
- [GNU C Library — `FOPEN_MAX`](https://www.gnu.org/software/libc/manual/html_node/Opening-Streams.html) — used in the bonus to size the fd buffer array
- [Static variables in C (cppreference)](https://en.cppreference.com/w/c/language/storage_duration) — explains why `static` preserves state between calls
- [42 `get_next_line` subject (Harm's overview)](https://harm-smits.github.io/42docs/projects/get_next_line) — community walkthrough of the project requirements

### AI usage

AI (Claude by Anthropic) was used during this project for the following tasks:

- **Generating this README** — the structure, algorithm explanation, and formatting of this file were produced with AI assistance based on the implemented source code.
- **Debugging logic** — AI was consulted to reason about edge cases such as a file with no trailing newline, `BUFFER_SIZE = 1`, and EOF handling.