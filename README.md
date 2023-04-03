# Simple Shell

## Introduction
Simple Shell is a basic shell implementation written in C that allows you to execute commands and interact with your operating system. The goal of this shell is to provide a simple and easy-to-understand implementation that can be used as a starting point for more complex shell projects.

## Getting Started
To use Simple Shell, follow these simple steps:
1. Clone the repository to your local machine.
2. Navigate to the root directory of the repository.
3. Run the `make` command to compile the shell:
    ```
    $ make
    ```
4. Run the shell by executing the `simple_shell` executable:
    ```
    $ ./simple_shell
    ```

## Usage
Once you have started the shell, you can enter commands just like you would in any other shell. Simple Shell supports basic command execution, as well as input and output redirection. The shell also includes built-in commands such as `exit` and `cd`.

### Built-in Commands
- `exit`: Exits the shell.
- `cd`: Changes the current working directory. Usage: `cd [directory]`

### Input and Output Redirection
Simple Shell supports input and output redirection using the `<` and `>` characters respectively. You can use these characters to redirect input and output to and from files. For example:
