# Minishell - A Simple UNIX Shell Implementation

A minimal shell implementation in C that mimics the behavior of bash, supporting pipes, redirections, environment variables, and several built-in commands.

## Directory Structure

- `src/parse/` - Tokenization, quote handling, variable expansion, syntax checking
- `src/exec/` - Command execution, pipes, redirections, path resolution
- `src/builtin/` - 7 built-in commands (echo, cd, pwd, export, unset, env, exit)
- `src/utils/` - Memory management, signal handling, utilities
- `libft/` - Custom C library
## How It Works

### 1. **Main Loop** (`src/main.c`)

The main program follows this sequence:

```c
// Initialize shell data and environment variables
initial_data(&data);    // Set exit_code=0, signals setup
make_env(&data, env);   // Copy system environment

// Infinite loop for command processing
while (1) {
    line = readline("minishell> ");      // Read user input
    if (!parseline(&data, line))          // Parse input
        continue;
    exec(&data);                          // Execute command
    free_token_list(&data.token);         // Clean up
    free_cmd_list(&data.cmd);
}
```

**Key Data Structures:**

```c
// Token: Represents parsed elements (commands, arguments, redirections, pipes)
typedef struct s_token {
    char *str;           // Token string value
    int type;            // CMD, ARG, PIPE, INPUT, HEREDOC, TRUNCATE, APPEND
    struct s_token *prev;
    struct s_token *next;
} t_token;

// Command: Represents executable commands with I/O redirection
typedef struct s_cmd {
    char **cmd_param;    // Command and its arguments
    int infile;          // Input file descriptor
    int outfile;         // Output file descriptor
    bool skip_cmd;       // Flag to skip execution
    struct s_cmd *prev;
    struct s_cmd *next;
} t_cmd;

// Data: Main shell state
typedef struct s_data {
    t_token *token;      // Parsed tokens list
    t_cmd *cmd;          // Commands to execute
    t_list *env;         // Environment variables
    int pip[2];          // Pipe file descriptors
    int exit_code;       // Last command exit code
} t_data;
```

---

### 2. **Parsing Phase** - Converting raw input to commands

1. **Tokenization** - Split input by special chars (`|`, `<`, `>`, `>>`), respecting quotes
   - Example: `echo hello | grep x > file.txt` → `[echo] [hello] [|] [grep] [x] [>] [file.txt]`

2. **Quote Handling** - Single quotes prevent expansion, double quotes allow variable expansion
   - `'$VAR'` → literal "$VAR", `"$VAR"` → environment value

3. **Variable Expansion** - Replace `$VAR` with environment values, `$?` with exit code

4. **Syntax Check** - Validate pipes/redirections have proper targets

5. **Command Creation** - Convert tokens to executable commands with file descriptors for I/O

---

### 3. **Execution Phase** - Running commands (`src/exec/exec.c`)

#### Built-in Commands Execution

Built-in commands (echo, cd, pwd, export, unset, env, exit) are executed directly in the current shell process:

```c
// Check if command is built-in
bool is_builtin(char *cmd) {
    return ft_strncmp("echo", cmd) == 0 ||
           ft_strncmp("cd", cmd) == 0 ||
           // ... other built-ins
           ft_strncmp("exit", cmd) == 0;
}

// Execute built-in command
if (is_builtin(cmd->cmd_param[0])) {
    if (strcmp(cmd->cmd_param[0], "echo") == 0)
        data->exit_code = ft_echo(cmd->cmd_param);
    // ... other built-ins
}
```

#### External Command Execution

External commands use fork/exec pattern:

```c
void execute_cmd(t_data *data, t_cmd *cmd, int *pip) {
    pid_t pid = fork();
    
    if (pid == 0) {                    // Child process
        redirect_io(data, cmd, pip);   // Set up pipes/redirections
        execve(cmd_path, cmd->cmd_param, env_array);  // Replace process
    } else {                           // Parent process
        // Store child PID for waiting
        // Continue to next command if pipe exists
    }
}
```

#### Pipe Handling

For `cmd1 | cmd2`:
1. Create pipe: `pipe(fd)` → fd[0] (read), fd[1] (write)
2. cmd1's stdout → pipe[1]
3. cmd2's stdin ← pipe[0]
4. Wait for all children with `waitpid()`

#### Redirection Handling

```c
// Input redirection: cat < input.txt
open("input.txt", O_RDONLY) → fd
dup2(fd, STDIN_FILENO)

// Output redirection: echo hello > output.txt
open("output.txt", O_WRONLY | O_CREAT | O_TRUNC) → fd
dup2(fd, STDOUT_FILENO)

// Append redirection: echo text >> file.txt
open("file.txt", O_WRONLY | O_CREAT | O_APPEND) → fd
dup2(fd, STDOUT_FILENO)
```

#### Here-Document Handling (`src/exec/here_doc.c`)

`cmd << DELIMITER` creates temporary content until delimiter is found:

```bash
# Example: cat << EOF
# line1
# line2
# EOF

// Implementation:
// 1. Store lines until DELIMITER is encountered
// 2. Create temporary file or pipe with accumulated content
// 3. Set as stdin for command
```

---

### 4. **Built-in Commands**

| Command | Function | Example |
|---------|----------|----------|
| `echo` | Print with spaces, `-n` suppresses newline | `echo -n "hello"` |
| `cd` | Change directory, update PWD | `cd /tmp` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variable | `export VAR=value` |
| `unset` | Remove environment variable | `unset VAR` |
| `env` | List all environment variables | `env` |
| `exit` | Exit shell with code | `exit 42` |

---

### 5. **Signal Handling** (`src/utils/signal.c`)

Handles user signals:
- **Ctrl+C** (`SIGINT`): Sends interrupt to current process (if `g_signal_pid > 0`)
- **Ctrl+\\** (`SIGQUIT`): Not redirected in minishell
- **Ctrl+D** (`EOF`): Terminates readline, exits shell

---

## Compilation

```bash
make              # Build the project
make re           # Rebuild from scratch
make clean        # Remove object files
./minishell       # Run the shell
```

## Example Usage

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

## Limitations

- No background processes (`&`), globbing (`*`, `?`), or job control
