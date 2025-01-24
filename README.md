# PIPEX
x This project aims to deepen your understanding of the two concepts that you already know: Redirections and Pipes. It is
an introductory project for the bigger UNIX projects that will appear later on in the cursus

# System Calls in C

The following system calls are fundamental for process management, file handling, and inter-process communication in C. Each plays a key role in low-level system programming.

## 1. `access`

Checks a user's permissions for a file.

```c
#include <unistd.h>

int access(const char *pathname, int mode);
```

- **Parameters**:
  - `pathname`: Path to the file.
  - `mode`: Access mode (e.g., `R_OK`, `W_OK`, `X_OK`, `F_OK`).
- **Returns**: `0` if the requested access is permitted; `-1` otherwise.
- **Example**:
```c
if (access("example.txt", R_OK) == 0) {
    printf("File is readable.\n");
} else {
    perror("Access error");
}
```

---

## 2. `dup`

Duplicates a file descriptor.

```c
#include <unistd.h>

int dup(int oldfd);
```

- **Parameters**:
  - `oldfd`: The file descriptor to duplicate.
- **Returns**: A new file descriptor that refers to the same resource, or `-1` on error.
- **Example**:
```c
int newfd = dup(oldfd);
```

---

## 3. `dup2`

Duplicates a file descriptor to a specific value.

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);
```

- **Parameters**:
  - `oldfd`: File descriptor to duplicate.
  - `newfd`: File descriptor to overwrite.
- **Example**:
```c
dup2(oldfd, 1); // Redirects stdout to oldfd
```

---

## 4. `execve`

Executes a new program, replacing the current process.

```c
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);
```

- **Parameters**:
  - `pathname`: Path to the executable.
  - `argv`: Arguments array.
  - `envp`: Environment variables.
- **Returns**: Only on error (`-1`).
- **Example**:
```c
char *args[] = {"/bin/ls", "-l", NULL};
execve(args[0], args, NULL);
```

---

## 5. `exit`

Terminates the current process.

```c
#include <stdlib.h>

void exit(int status);
```

- **Parameters**:
  - `status`: Exit status of the process (0 for success, non-zero for errors).
- **Example**:
```c
exit(0); // Normal termination
```

---

## 6. `fork`

Creates a new process by duplicating the current one.

```c
#include <unistd.h>

pid_t fork(void);
```

- **Returns**:
  - `0` to the child process.
  - The child's PID to the parent process.
- **Example**:
```c
pid_t pid = fork();
if (pid == 0) {
    printf("This is the child process.\n");
} else {
    printf("This is the parent process.\n");
}
```

---

## 7. `pipe`

Creates a unidirectional communication channel (pipe).

```c
#include <unistd.h>

int pipe(int pipefd[2]);
```

- **Parameters**:
  - `pipefd`: Array of two file descriptors (`pipefd[0]` for reading, `pipefd[1]` for writing).
- **Returns**: `0` on success; `-1` on error.
- **Example**:
```c
int pipefd[2];
pipe(pipefd);
write(pipefd[1], "Hello", 5);
char buffer[6];
read(pipefd[0], buffer, 5);
buffer[5] = '\0';
printf("%s\n", buffer); // Outputs "Hello"
```

---

## 8. `wait`

Waits for a child process to terminate.

```c
#include <sys/wait.h>

pid_t wait(int *wstatus);
```

- **Parameters**:
  - `wstatus`: Pointer to store the child's exit status.
- **Returns**: The PID of the terminated child, or `-1` on error.
- **Example**:
```c
pid_t child_pid = fork();
if (child_pid == 0) {
    exit(0);
} else {
    wait(NULL);
    printf("Child process terminated.\n");
}
```

---

## 9. `waitpid`

Waits for a specific child process to terminate.

```c
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *wstatus, int options);
```

- **Parameters**:
  - `pid`: PID of the child to wait for.
  - `wstatus`: Pointer to store the child's exit status.
  - `options`: Additional options (e.g., `WNOHANG`).
- **Example**:
```c
waitpid(child_pid, NULL, 0);
```

---

## Key Points

- These system calls are essential for low-level programming, especially in managing processes and files.
- Always check the return values of system calls for error handling.
- Be cautious when working with `fork`, `pipe`, and `execve` to avoid resource leaks or undefined behavior.

---

