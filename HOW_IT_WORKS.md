# How Minishell Works

This document explains the internal architecture of the project and the path a command takes from user input to execution.

## 1. Main Loop

The main program in `src/main.c` initializes the shell state and environment, then repeatedly reads, parses, executes, and cleans up one command line at a time:

```c
initial_data(&data);
make_env(&data, env);

while (1) {
    line = readline("minishell> ");
    if (!parseline(&data, line))
        continue;
    exec(&data);
    free_token_list(&data.token);
    free_cmd_list(&data.cmd);
}
```

The shell state is stored in `t_data`. Input is first represented as a linked list of `t_token` nodes, then converted into a linked list of `t_cmd` nodes for execution.

```c
typedef struct s_token {
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_cmd {
    char **cmd_param;
    int infile;
    int outfile;
    bool skip_cmd;
    struct s_cmd *prev;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data {
    t_token *token;
    t_cmd *cmd;
    t_list *env;
    int pip[2];
    int exit_code;
} t_data;
```

## 2. Parsing

The parsing code in `src/parse/` transforms the raw input line into executable command structures:

1. Tokenization separates words and operators such as `|`, `<`, `>`, and `>>`, while respecting quotes.
2. Quote handling keeps text in single quotes literal and allows variable expansion inside double quotes.
3. Variable expansion replaces environment variables and `$?` with their current values.
4. Syntax checking verifies that pipes and redirections have valid operands.
5. Command creation groups tokens into commands and prepares input and output file descriptors.

For example, `echo hello | grep x > file.txt` becomes a token sequence containing `echo`, `hello`, `|`, `grep`, `x`, `>`, and `file.txt`, then becomes two command nodes connected by a pipe.

## 3. Execution

The execution code in `src/exec/` chooses between built-in commands and external programs.

### Built-ins

Built-ins that must modify the current shell state, such as `cd`, `export`, `unset`, and `exit`, are handled by the shell process. The supported built-ins are:

| Command | Purpose |
|---------|---------|
| `echo` | Print arguments, with optional `-n` |
| `cd` | Change directory and update `PWD` |
| `pwd` | Print the current directory |
| `export` | Add or update an environment variable |
| `unset` | Remove an environment variable |
| `env` | Print environment variables |
| `exit` | Exit with a status code |

### External commands

External commands use the `fork`/`execve` model:

1. The parent creates a child process with `fork()`.
2. The child configures its pipes and redirections.
3. The child resolves the executable path and calls `execve()`.
4. The parent waits for the child processes and stores the resulting exit status.

## 4. Pipes and Redirections

For `cmd1 | cmd2`, `pipe()` creates a read end and a write end. The first command's standard output is connected to the write end, and the second command's standard input is connected to the read end. The parent closes unused descriptors and waits for all children.

Redirections are applied with `open()` and `dup2()`:

```c
open("input.txt", O_RDONLY);
dup2(fd, STDIN_FILENO);

open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
dup2(fd, STDOUT_FILENO);

open("file.txt", O_WRONLY | O_CREAT | O_APPEND);
dup2(fd, STDOUT_FILENO);
```

The corresponding shell syntax is `<`, `>`, and `>>`. A here-document such as `cat << EOF` reads lines until the delimiter is reached and uses the collected content as the command's standard input. Its implementation is in `src/exec/here_doc.c`.

## 5. Signals and Cleanup

Signal handling is implemented in `src/utils/signal.c`:

- `Ctrl+C` (`SIGINT`) interrupts the active command when a child process is running.
- `Ctrl+\\` (`SIGQUIT`) is handled according to minishell behavior.
- `Ctrl+D` (`EOF`) ends the readline loop and exits the shell.

After each command line, token and command lists are freed before the next prompt. Environment data and other global shell state are released when the shell exits.