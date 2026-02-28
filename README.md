# Minishell - As Beautiful as a Shell can be

**Inspired by Bash, this project explores the depths of system calls, process management, and lexical analysis to create a robust command-line interpreter from scratch.**

## Features

- Execute external commands
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- Here-document support
- Basic signal handling (`Ctrl+C`, `Ctrl+\`)


### 🟢 Part 1: Parsing & Tokenization
* **Goal**: Transform user input into a manageable command list.
* **Concepts**:
    * **Tokenization**: Splitting input by metacharacters while respecting double/single quotes.
    * **Expansion**: Dynamically replacing `$VAR` with environment values and handling the `$?` exit status.

### 🔵 Part 2: Execution Engine
* **Goal**: High-performance command dispatching.
* **Concepts**:
    * **Path Resolution**: Searching the `PATH` environment variable to locate binary executables.
    * **Builtins**: Implementing internal logic for `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
    * **Pipes**: Creating a pipeline architecture where the output of one process becomes the input of the next.

### 🟡 Part 3: Redirections 
* **Goal**: Managing data flow to and from files.
* **Features**:
    * **📥 Input/Output**: Using `<` and `>` to redirect standard streams.
    * **📝 Append & Heredoc**: Implementing `>>` for non-destructive writes and `<<` for interactive multi-line input.

### 🔴 Part 4: Technical Polish
* **Goal**: Stability and memory integrity.
* **Concepts**:
    * **Environment Management**: Maintaining a custom copy of the environment linked list.
    * **Memory Cleanup**: Ensuring every `malloc` has a corresponding `free`, passing all `Valgrind` leak checks.



## 💡 Installation & Usage
```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
./minishell
```
### Example
```
>minishell$ echo "Hello World"
Hello World
>minishell$ ls -l | grep minishell
-rwxr-xr-x 1 user group 12345 Nov 29 16:00 minishell
```
