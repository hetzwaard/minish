# MINISH 🍀

### Mini UNIX Shell

Minish is a small shell written in C for the 42 curriculum (team project). It runs a prompt, parses what you type, and executes commands with pipes, redirections, variables, wildcards, and heredocs.

The goal: learn how a shell really works while keeping the code readable and safe.

---
## Features
- Prompt loop with correct exit codes
- Lexer + parser building a simple execution tree
- Builtins:
  - `echo` (with -n)
  - `cd` (relative / absolute / `~` / `-`)
  - `pwd`
  - `export` / `unset`
  - `env`
  - `exit`
- External commands via `execve`
- PATH lookup + direct path execution
- Redirections: `<`, `>`, `>>`, heredoc `<<`
- Pipes (any length)
- Parentheses / subshell grouping (bonus)
- Variable expansion: `$VAR`, `$?`
- Wildcards (`*`) (bonus)
- Proper quote rules (single vs double)
- Safe heredoc handling (own signal mode)
- Clean signal behavior (Ctrl+C, Ctrl+\, Ctrl+D)
- Clear error messages
- Careful memory cleanup

---
## Bonus Implemented
- Parentheses (grouped commands)
- Wildcard expansion
- Smarter variable replacement
- Strong heredoc handling

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
Flow:
1. Read line (readline)
2. Lex into tokens
3. Expand (vars, wildcards, heredocs)
4. Build nodes / tree
5. Execute (pipes, redirs, subshells, builtins)
6. Free stuff, loop again

---
## Key Modules
- Parsing: tokens, wildcards, `$VAR` handling, tree build
- Execution: argv build, path search, builtins, redirs, pipes, subshell
- Redirections: open/dup logic (`redir_*` files)
- Heredoc: delimiter + temporary storage + signals
- Signals: different modes (prompt / child / heredoc)
- Environment: internal copy you can modify
- Freeing: every allocation has a matching cleanup path
- Errors: grouped helpers for consistent output

---
## Error Handling
We try to fail early and clearly.

Examples:
```
🚧 MINISH > echo "
syntax error: unclosed quote

🚧 MINISH > ls no_such_file
ls: cannot access 'no_such_file': No such file or directory

🚧 MINISH > nosuchcommand
nosuchcommand: command not found

🚧 MINISH > ./script.sh
./script.sh: Permission denied
```
Rules of thumb:
- Detect syntax issues before execution (quotes, parentheses, unexpected tokens)
- `127` = command not found, `126` = cannot execute, `128 + n` = signal n
- Use our own wrappers for consistent formatting

---
## Signals
Behavior aims to feel familiar if you use bash.

| Context    | Ctrl+C (SIGINT)           | Ctrl+\ (SIGQUIT) | Ctrl+D (EOF)                    |
|------------|---------------------------|------------------|---------------------------------|
| Prompt     | Cancel current line       | Ignored          | Exit shell if line is empty     |
| Child proc | Interrupt program         | Quit if app reacts| N/A (read by parent readline)  |
| Heredoc    | Abort current heredoc     | Ignored          | Ends heredoc if line == delim   |

Ctrl+D does not send a signal; it's an EOF from the terminal. If the current input buffer is empty we exit cleanly (like bash). Inside heredoc, only the delimiter closes it—EOF acts like end-of-input if reached unexpectedly.

---
## Building
Prerequisites:
- `make`, POSIX toolchain
- `readline` development headers (e.g. on Debian/Ubuntu: `sudo apt install libreadline-dev`)

Clone it:
```bash
git clone https://github.com/hetzwaard/minish --recursive && cd minish
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
- `*` expands to matching files (no dotfiles unless pattern starts with `.`)
- `$VAR` and `$?` expand unless in single quotes
- Text around expansions is joined naturally

---
## Development Utilities
`libft` is our small helper library (string, memory, list, printf-style funcs).

---
## Credits
Built as a 42 school team project. Name inspired by the tiny folk in *The Legend of Zelda: The Minish Cap*.

---
Enjoy exploring Minish! 🍀
