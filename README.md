# Minishell

## Overview
Minishell is a simplified Unix shell that mimics basic `bash` behavior.  
It supports command execution, built-in commands, pipes, redirections, and basic signal handling.

## Authors
- doudoumai007
- yopeng2025 

## Features
- Execute external commands
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- Here-document support
- Basic signal handling (`Ctrl+C`, `Ctrl+\`)

## Installation & Usage
```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
./minishell
```

## Example
```
>minishell$ echo "Hello World"
Hello World
>minishell$ ls -l | grep minishell
-rwxr-xr-x 1 user group 12345 Nov 29 16:00 minishell
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.
