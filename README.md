# A Simple Shell Implementation in C

A simple shell implementation in C, allowing users to execute commands and interact with the operating system.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Usage](#usage)
4. [Functions](#functions)
5. [Files](#files)
6. [Authors](#authors)

## Introduction

This project aims to create a basic shell that can execute commands and provide a simple interface for users to interact with the operating system. The shell is written in C and uses the `fork` and `execve` system calls to execute commands.

## Features

- Execute commands with arguments
- Handle environment variables
- Search for executable files in the `PATH` environment variable
- Provide a simple interface for users to interact with the operating system

## Usage

1. Compile the code using `gcc`: 
    ```hsh
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
    ```
2. Run the shell:
    ```hsh
    ./hsh
    ```
3. Type commands and press Enter to execute them

## Functions

- `_getenv`: Retrieves the value of an environment variable
- `find_path`: Searches for an executable file in the `PATH` environment variable
- `get_flags`: Tokenizes the user input into arguments
- `handle_error`: prints the last error in the same syntax as sh
- `handle_arg`: Analyzes the first argument and executes the corresponding action
- `main`: The main function of the shell, responsible for reading user input and executing commands

## Files

- `env.c`: Contains functions for handling environment variables and searching for executable files
- `main.h`: Header file containing function declarations
- `shell.c`: Contains the main function of the shell
- - `shell_utils.c`: contains the functions to analyze and execute the inputs.

## Authors
- Nacho Machado
- Owen Fernandez
