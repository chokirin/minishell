# minishell

`minishell` is a small interactive Unix shell written in C as part of the
42 curriculum. It reads commands with GNU Readline, parses shell syntax,
expands environment variables, and executes built-ins and external programs.

## Features

- Interactive prompt with Readline history
- Environment-variable expansion with `$NAME` and `$?`
- Single and double quotes
- Pipelines with `|`
- Input and output redirection:
  - `<` read from a file
  - `>` write to a file
  - `>>` append to a file
  - `<<` here-document input
- Signal handling for interactive use and here-documents
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Exit-status propagation through `$?`

## Requirements

- A C compiler compatible with the project Makefile
- `make`
- GNU Readline development headers and library
- `valgrind` for the optional memory-checking target

The current Makefile points Readline at the Homebrew locations
`/opt/homebrew/opt/readline/include` and `/opt/homebrew/opt/readline/lib`.
On another platform, install Readline and update `READLINE_INC` and
`READLINE_LIB` in `Makefile` to match the local installation.

## Build

From the repository root:

```sh
make
```

Useful targets:

```sh
make clean    # Remove object files
make fclean   # Remove object files, libraries, and the executable
make re       # Rebuild from scratch
make valgrind # Run minishell under Valgrind
```

## Run

Start the shell with:

```sh
./minishell
```

Example commands:

```sh
minishell $> echo "hello $USER"
minishell $> export PROJECT=minishell
minishell $> printf '%s\n' "$PROJECT" | wc -c
minishell $> cat < input.txt > output.txt
minishell $> cat << EOF
> a line from the here-document
> EOF
```

Use `exit` or press `Ctrl-D` at an empty prompt to leave the shell.

## Project layout

```text
incl/          Public project headers
src/
  builtin/     Shell built-ins and environment management
  execution/   External command execution helpers
  expander/    Environment-variable expansion
  libft/       Project utility library
  main/        Shell entry point and main loop
  parsing/     Tokenization, syntax checks, and command construction
  pipe/        Pipeline setup and execution
  redirect/    File redirection and here-documents
  signal/      Interactive signal handling
Makefile       Build and development targets
```

## Notes

This project is intended for interactive Unix-like environments. Commands
that are not built in are resolved using the shell environment and executed
as external programs. The shell maintains its own environment for built-ins
such as `cd`, `export`, and `unset`.

The repository does not currently include an automated test target. Manual
testing can be performed by comparing common commands and exit statuses with
the system shell, especially around quoting, redirections, pipelines, and
signals.

## License

No license file is currently included in this repository.
