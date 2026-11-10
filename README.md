# Minishell

A small Unix shell written in C for the 42 curriculum.

This project helped me understand what happens between typing a command and running a process: tokenising input, parsing commands, handling redirections and pipes, managing the environment, and dealing with signals.

## Build and run

Requires a C compiler, GNU Make and the Readline development library.

```bash
make
./minishell
```

The shell uses Readline for interactive input. Try simple commands, environment variables, pipes and redirections.

```sh
echo hello
pwd
echo hello | cat
echo hello > output.txt
```

## Code

- `srcs/lexing/` and `srcs/parser/`: interpret command input
- `srcs/execute/` and `srcs/pipes/`: execute commands and handle pipelines
- `srcs/redirections/`: file descriptors and redirections
- `srcs/builtins/`: built-in shell commands
- `srcs/signaux/`: signal handling

The project uses a local copy of Libft in `libft_19/`.

## What I learned

Working in C with processes, file descriptors and memory management made debugging much more concrete. This is a learning project, not a replacement for Bash.
