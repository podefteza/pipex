# 🔗 pipex

`pipex` is a custom implementation of Unix-like piping, designed to create a pipeline between two commands, emulating a simple shell piping mechanism. This program leverages processes, pipes, and file descriptors for efficient data transfer, allowing two commands to run sequentially, where the output of the first command serves as the input for the second command.

## Table of Contents
1. [Overview](#overview)
2. [Project Flow](#project-flow)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Program Details](#program-details)

## Overview

The core of `pipex` relies on key Unix concepts:

- **Processes**: Independent instances of a program that can execute in parallel.
- **Pipes**: Temporary memory buffers for inter-process communication, allowing data to be passed efficiently between processes.
- **File Descriptors**: Numerical handles to open files, such as `stdin` (0), `stdout` (1), and `stderr` (2).
- **STDIN_FILENO and STDOUT_FILENO**: Defined in `<unistd.h>`, these macros are commonly used for I/O redirection.

## Project Flow

This project uses two separate child processes to execute two commands in sequence, using pipes for data transfer:

1. **First Command**:
   - A child process is created to execute the first command.
   - The `dup2()` function redirects `STDIN_FILENO` to the input file (`infile`) and `STDOUT_FILENO` to the pipe’s write end.
   - The command output is directed into the pipe.

2. **Second Command**:
   - A second child process executes the second command.
   - `STDIN_FILENO` is redirected to the pipe’s read end, and `STDOUT_FILENO` is redirected to the output file (`outfile`).
   - This command reads the first command’s output from the pipe and writes the final result to `outfile`.

This setup mimics a shell pipe, allowing the first command’s output to be passed directly as input to the second command.

## Installation

Clone the repository and compile the program:

```bash
git clone https://github.com/podefteza/pipex/
cd pipex
make
```

## Usage

The program requires an input file, two commands, and an output file:

```bash
./pipex infile "cmd1" "cmd2" outfile
```
Example:
```bash
./pipex input.txt "ls -l" "grep .c" output.txt
```
If incorrect arguments are provided, pipex will display:
```bash
Usage: ./pipex "infile" "cmd1" "cmd2" "outfile"
```

## Program Details

### Argument and File Checks

- **Argument Count**: If `argc` is not 5, the program exits with an error message.
- **File Checks**:
  - If `infile` doesn’t exist or lacks permission, it opens a null command to simulate no input and allows the program to keep running.
  - If `outfile` doesn’t exist, it creates it with permissions `0666` (all users can read and write but cannot execute).
  - If `outfile` lacks permission, the program exits with `EXIT_FAILURE`.
  - On success, `infile` and `outfile` are opened, and their file descriptors are returned.

### Command Parsing

Commands are parsed into a 2D array using helper functions:

- The command strings are split by spaces to separate the executable and its arguments.
- If quotes are detected, the quotes are removed, and arguments are joined accordingly.

**Example**:
```c
./pipex "infile" "ls -l" "grep 42" "outfile"

commands[0][0] = ls;
commands[0][1] = -l;
commands[1][0] = grep;
commands[1][1] = 42;
commands[2][0] = NULL
```
```c
./pipex "infile" "cat" "awk '{count++} END {printf \"my count: %i\", count}'" "outfile"
commands[0][0] = cat
commands[1][0] = awk
commands[1][1] = {count++} END {printf "my count: %i", count}
```


### Path Search

The program searches for the command path with `find_command`:

- `cmd_is_path`: Checks if the command is given as an explicit path.
- `get_path_from_env`: Retrieves paths from the environment variable `PATH`.
- `search_in_path`: Iterates through each path directory to locate the command.
- `build_path`: Constructs the full path for the command.

If the cmd1 isn't found, the program keeps executing, and only if the cmd2 isn’t found, the program stops with an error message and exits.

### Process Forking and Execution

`pipex` creates a pipe and forks two child processes:

1. **First Process**:
   - Reads from `infile` and writes to the pipe.
   - Duplicates `infile` to `STDIN_FILENO` and the pipe’s write end to `STDOUT_FILENO`.
   - Executes the command if found, replacing the current process with `execve`.

2. **Second Process**:
   - Reads from the pipe and writes to `outfile`.
   - Duplicates the pipe’s read end to `STDIN_FILENO` and `outfile` to `STDOUT_FILENO`.
   - Executes the command similarly to the first process.

Finally, the program closes pipes, waits for processes to complete, and returns the exit status.

### Error Handling

- Displays error messages for file or permission issues.
- Handles cases where commands are not found by checking command paths and arguments.
- Exits with an appropriate status, including handling cases where both commands are invalid.
