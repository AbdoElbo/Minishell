# Minishell 🐚

This project has been created as part of the 42 curriculum by **aelbouaz** and **hkonstan**.

## 📖 Description

Minishell is a 42 School project that challenges you to build your own simplified version of a **shell**, similar to `bash`. The goal is to understand how a shell actually works under the hood — parsing user input, handling processes, managing pipes and redirections, and dealing with signals — all without relying on any shell logic already built into the system.

By the end of this project, your shell should be able to:

- Display a prompt and wait for a command
- Handle a working history (readline)
- Search and launch the right executable (using `PATH` or relative/absolute paths)
- Handle **single quotes** and **double quotes** properly
- Implement redirections:
  - `<` — input redirection
  - `>` — output redirection
  - `<<` — heredoc
  - `>>` — append output redirection
- Handle **pipes** (`|`) so the output of one command becomes the input of the next
- Handle environment variables (`$VAR`, `$?`, etc.)
- Implement signal handling (`ctrl-C`, `ctrl-D`, `ctrl-\`) matching bash's behavior
- Implement built-ins:
  - `echo` (with `-n` option)
  - `cd` (relative or absolute path)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## ⚙️ Instructions

### Prerequisites

Make sure you have `make`, a compatible compiler, and the `readline` library installed on your system.

### Step 1 — Compile

In your terminal, navigate to the project directory and run:

```bash
make
```

This will compile the source files and produce the `minishell` executable.

### Step 2 — Run

Launch the shell with:

```bash
./minishell
```

You'll be dropped into a prompt where you can type commands just like you would in a regular shell:

```bash
minishell$ ls -la | grep .c | wc -l
```

## 🧠 What This Project Covers

- Parsing and tokenizing raw input
- Process creation and management (`fork`, `execve`, `wait`)
- File descriptor manipulation and redirections
- Signal handling
- Environment variable management
- Memory management in a long-running, interactive program

## 📚 Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

---
*Part of the 42 School common core curriculum.*
