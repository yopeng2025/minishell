# Minishell - A Simple UNIX Shell Implementation

A minimal shell implementation in C that mimics the behavior of bash, supporting pipes, redirections, environment variables, and several built-in commands.

For an explanation of the internal architecture and command-processing flow, see [HOW_IT_WORKS.md](HOW_IT_WORKS.md).

## Directory Structure

- `src/parse/` - Tokenization, quote handling, variable expansion, syntax checking
- `src/exec/` - Command execution, pipes, redirections, path resolution
- `src/builtin/` - 7 built-in commands (echo, cd, pwd, export, unset, env, exit)
- `src/utils/` - Memory management, signal handling, utilities
- `libft/` - Custom C library
---

## Compilation

```bash
make              # Build the project
make re           # Rebuild from scratch
make clean        # Remove object files
./minishell       # Run the shell
```

## Usage

```bash
$ minishell
minishell> echo "Hello, World!"
Hello, World!

minishell> export MY_VAR=test
minishell> echo $MY_VAR
test

minishell> ls -la | grep minishell
-rwxr-xr-x  1 user  group  12345 Nov 27 14:32 minishell

minishell> cat < input.txt > output.txt

minishell> cat input.txt | grep pattern | sort > result.txt

minishell> pwd
/home/user/minishell

minishell> exit 0
```

## Testing with 42-minishell-tester

Use the `42-minishell-tester` project to test the shell commands and check for memory leaks.

1. Make sure the `42-minishell-tester` directory is located in your home directory or in the `minishell` directory.
2. Uncomment the tester-specific `main` function and comment out the simple version of `main`.
3. Run `mstest m` to test all commands.
4. Run `mstest vm` to check for memory leaks.
5. Run `mstest ne` to test minishell with no environment variables.


## Limitations

- No background processes (`&`), globbing (`*`, `?`), or job control
