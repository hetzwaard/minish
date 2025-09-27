# MINISH 🍀

### Mini UNIX Shell

Minish is a small UNIX-like shell written in C. It implements a command-line interpreter with parsing, execution, environment variable management, redirections, pipes, heredocs, wildcard expansion, and robust signal/error handling. It focuses on clean modular architecture and safe memory management.

---
## Features
- Command prompt with interactive loop and proper exit status propagation
- Lexer + parser building an AST / execution tree
- Builtins:
  - `echo` (with -n)
  - `cd` (relative / absolute / `~` / `-`)
  - `pwd`
  - `export` / `unset`
  - `env`
  - `exit`
- External command execution via `execve`
- PATH resolution + relative/absolute execution
- Redirections: `<`, `>`, `>>`, heredoc `<<`
- Pipes: arbitrary length pipelines
- Parentheses / subshell grouping (bonus)
- Environment variable expansion: `$VAR`, `$?`
- Wildcard expansion (`*`) (bonus)
- Quote handling: single vs double quote semantics
- Heredoc with signal-safe behavior and delimiter management
- Signal handling: `SIGINT`, `SIGQUIT` behavior aligned with bash-like UX
- Graceful error reporting with categorized messages
- Defensive memory management + full cleanup paths

---
## Bonus Implemented
- Parentheses for grouped command execution
- Wildcard (globbing) expansion
- Advanced variable replacement logic (dollar parsing module)
- Robust heredoc handling with dedicated signal mode

---
## Architecture Overview
```
include/            Public headers (main: minishell.h)
include/libft/      Custom libc-like helper library (libft)
src/
  cdll/             Circular doubly linked list utilities (token / node mgmt)
  env/              Environment read/write helpers
  exec/             Execution engine, builtins, redirections, pipes, subshell
  init/             Shell + heredoc initialization
  parse/            Lexer, tokenization, tree builder, wildcard & dollar tools
  sig/              Signal handling layers (shell, heredoc, exec, pipex)
  utils/            Common helpers, error & free modules
```
Core flow:
1. Read line (readline)
2. Lex into tokens (respecting quotes, operators)
3. Expand (env vars, wildcards, heredocs pre-processing)
4. Build execution tree / nodes
5. Execute recursively (pipelines, redirs, subshells, builtins)
6. Cleanup + loop

---
## Key Modules
- Parsing (`parse/lexer.c`, `parse/token/*`, `parse/tt/*`): token kinds, redirection specs, wildcard & dollar expansion, directory listing
- Execution (`exec/`): argument vector build, filename resolution, builtins dispatch, pipeline + redirection orchestration
- Redirections (`exec/ops/redir_*.c`): input, output, append, heredoc temp handling
- Heredoc (`cdll/cdll_heredoc.c`, `init/init_heredoc.c`): delimiter management + SIGINT isolation
- Signals (`sig/`): context-specific handlers (interactive vs child vs heredoc)
- Environment (`env/`): synchronized copy of `envp` with export formatting
- Memory cleanup (`utils/free/*`): structured destruction (tree, tokens, arrays)
- Errors (`utils/error/*`): categorized error messages (syntax, open, exec, quote, parenthesis)

---
## Error Handling Philosophy
- Syntax errors detected early (unclosed quotes, invalid parenthesis, unexpected token)
- Execution errors report via `perror` variant + custom wrappers
- Exit status follows POSIX where practical (`127` command not found, `126` permission, signal codes 128+n)

---
## Signals
| Context    | SIGINT (Ctrl+C)           | SIGQUIT (Ctrl+\) |
|------------|---------------------------|------------------|
| Prompt     | Aborts current line, NL   | Ignored          |
| Child proc | Default (interrupt)       | Default          |
| Heredoc    | Cancels heredoc, cleanup  | Ignored          |

---
## Building
Prerequisites:
- `make`, POSIX toolchain
- `readline` development headers (e.g. on Debian/Ubuntu: `sudo apt install libreadline-dev`)

Clone it:
```bash
git clone https://github.com/hetzwaard/minish --recursive
```
Build:
```bash
make
```
Rebuild from scratch:
```bash
make re
```
Clean objects / full cleanup:
```bash
make clean
make fclean
```

---
## Running
```bash
./minishell
```
Examples:
```
🍀 MINISH > echo hello world
hello world
🍀 MINISH > export PATH="$PWD/bin:$PATH"
🍀 MINISH > cat <<EOF | grep foo > out.txt
foo bar
baz
foo qux
EOF
🍀 MINISH > (echo inside && echo group) | wc -l
2
🍀 MINISH > ls *.c | wc -l
```

---
## Wildcards & Expansion
- `*` expands against current working directory (non-hidden) unless quoted
- `$VAR` and `$?` expanded unless within single quotes
- Consecutive expansions merged with surrounding literals

---
## Development Utilities
`libft` provides custom implementations of common libc helpers plus formatted output (`ft_printf`) and memory/string utilities.

---
## Contributing
Internal educational project; external PRs not expected. Fork if you want to experiment.

---
## Credits
Created as part of a shell programming exercise. Name inspired by *The Minish Cap* (The Legend of Zelda).

---
Enjoy exploring Minish! 🍀
