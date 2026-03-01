*This project has been created as part of the 42 curriculum by nalesso and [Partner's Name/GitHub].*

# Minishell

## Description

A minimalist shell developed in **C** that replicates the core functionalities of Bash. This project is a deep dive into the Unix system, focusing on process creation, synchronization, file descriptors, multiplexing, and robust input parsing. It was built collaboratively, strictly adhering to the 42 school coding norms and ensuring zero memory leaks.

## Features

- **Prompt & Parsing:** Displays a working prompt and handles complex parsing, including single (`'`) and double (`"`) quotes, as well as environment variable expansion (`$VAR`, `$?`).
- **Execution:** Executes system binaries based on the `PATH` variable, as well as absolute and relative paths.
- **Built-in Commands:** Custom implementation of fundamental builtins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Pipes & Redirections:** Seamless handling of input/output redirection (`<`, `>`, `<<`, `>>`) and connecting commands via pipes (`|`).
- **Signal Handling:** Accurate response to interruption signals (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) matching Bash's behavior.
- **Process Management:** Proper handling of child processes using `fork`, `execve`, and `waitpid`.

## Instructions

**Compilation:**
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Recompile from scratch
```

**Execution:**
```bash
./minishell
```

## Core Concepts & Technologies

- **Language:** C
- **Build System:** Makefile
- **System Calls:** `fork`, `execve`, `waitpid`, `pipe`, `dup2`, `sigaction`
- **Concepts:** Abstract Syntax Tree (AST) / Tokenization, Process Control Block, Inter-Process Communication (IPC), Memory Management.
