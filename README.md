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
┌───────────────────────────────────────────────────────────────────────┐
│                         get_next_line(fd)                             │
│                                                                       │
│  1. Check if the static buffer already holds data from a prior read   │
│     └─► If so, call beeline() to try building a complete line from it │
│         └─► If a '\n' is found → return the line immediately          │
│                                                                       │
│  2. Call read() to fetch up to BUFFER_SIZE bytes from fd              │
│     ├─► bytesread < 0  → free line, return NULL (error)               │
│     └─► bytesread == 0 → flush buffer, return line as-is (EOF)        │
│                                                                       │
│  3. Append buffer content to the growing line via ft_linejoin()       │
│     └─► ft_linejoin copies s1 + s2 up to and including the first '\n' │
│                                                                       │
│  4. Call newlinebuf() on the static buffer                            │
│     └─► Shifts any bytes after the '\n' to the front of the buffer    │
│         so they are available on the next call                        │
│                                                                       │
│  5. If a '\n' was found → break and return the line                   │
│     Otherwise → loop back to step 2                                   │
└───────────────────────────────────────────────────────────────────────┘
```

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
└── bonus/
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

> If `BUFFER_SIZE` is not specified, the default value of `1` defined in the header will be used.

### Using `get_next_line` in your own project

Include the relevant files and header in your project, then call the function as follows:

```c
#include "get_next_line.h"

int main()
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);         // Always free the returned line
    }
    close(fd);
    return (0);
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