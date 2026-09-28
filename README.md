# 🐚 Minishell

> **Minishell** is a minimalist command-line interpreter (shell) developed as a group project for the 42 School curriculum. The goal is to recreate a working subset of `bash`, handling user input, process execution, environment variables, redirections, and pipes.

## 🙏 Acknowledgments
A special thank you to my wonderful partner, **narrospi**, with whom I built and completed this project. Collaboration, pair programming, and shared problem-solving made this achievement possible!

## 🎯 About the Project
Minishell challenges students to dive deep into UNIX system programming, process lifecycles, and low-level resource management in C.

The program loops to prompt the user, parses the input line into tokens, expands environment variables, handles single and double quotes, and executes commands safely using system calls.

 #### Key Features:
- **Prompt & History**: Displays a functional prompt and manages command history using the GNU Readline library.

- **Built-in Commands**: Implements custom versions of core bash built-ins (detailed below).

- **Redirections**: Supports standard input redirection (<), standard output redirection (>), append output (>>), and heredoc (<<).

- **Pipes (|)**: Connects the output of one command to the input of another seamlessly via file descriptors and process branching.

- **Environment Variables**: Expands variables (like \(USER or \)?) dynamically, including the exit status of the last executed command.

- **Signals**: Handles signals properly (Ctrl+C, Ctrl+D, Ctrl+Z) mimicking standard bash behavior without crashing or leaking memory.

## ⚙️ Detailed Built-in Commands
Unlike external binaries, built-ins are executed directly inside the shell process (when not piped) because they need to modify the shell's internal state or environment:

- **echo**: Prints arguments to the standard output. Supports the -n flag to omit the trailing newline.

- **cd**: Changes the current working directory. Handles relative paths, absolute paths, and updates both PWD and OLDPWD environment variables accordingly.

- **pwd**: Prints the absolute pathname of the current working directory to the standard output.

- **export**: Adds or updates environment variables without arguments (which prints the sorted list of exported variables) or with key-value pairs (e.g., export VAR=value).

- **unset**: Removes specified environment or shell variables, preventing them from being passed to future child processes.

- **env**: Prints all currently exported environment variables in a key=value format.

- **exit**: Safely terminates the minishell instance, optionally accepting a numeric exit status argument.

## 🛠️ Technologies Used
- **Language**: C

- **Core System Calls**: fork, execve, pipe, dup, dup2, wait, waitpid

- **File & Directory Management**: opendir, readdir, closedir, stat, lstat, access, unlink

- **Signal Handling**: signal, sigaction

- **Terminal Control**: tcsetattr, tcgetattr, ioctl

## 🚀 Getting Started
#### Prerequisites
- A UNIX-based operating system (Linux or macOS)

- gcc compiler

- make

- Readline library development headers (libreadline-dev on Linux / readline via Homebrew on macOS)

#### Compilation & Execution
1. Clone the repository:
  ```C
  git clone [https://github.com/VeraGD/Minishell_42.git](https://github.com/VeraGD/Minishell_42.git)
  cd minishell
  ```
2. Compile the project using the Makefile:

  ```C
   make
  ```

3. Run the executable:

 ```C
   ./minishell
  ```

## 🧹 Cleaning Up
To remove compiled object files:
```C
   make clean
  ```

To remove object files and the binary executable:
```C
   make fclean
  ```
To recompile from scratch:

```C
   make re
  ```
