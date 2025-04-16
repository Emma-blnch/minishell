# 🐚 Minishell

A team project from 42 Paris: rebuilding a simple Unix shell using **C** and system calls.  
This shell can execute commands, handle redirections and pipes, manage environment variables and signals — all in an interactive terminal interface.

> 🧑‍💻 Developed in collaboration with [Akim Hamini](https://github.com/akim775) 👥 during our 42 cursus.  

## 🚀 Project goals

- Understand how shells work under the hood (processes, file descriptors, signals)
- Use system calls such as `fork`, `execve`, `dup2`, `pipe`, `waitpid`, etc.
- Reimplement core Bash functionalities in a structured and maintainable way
- Develop a robust parser and a reliable command execution engine
- Manage edge cases, errors, and complex syntax

## 🔧 Features

✅ Execute external programs (absolute/relative paths)  
✅ Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`  
✅ Pipes `|` between multiple commands  
✅ Redirections: `>`, `>>`, `<`, `<<` (heredoc)  
✅ Environment variables support (`$USER`, `$?`, etc.)  
✅ Quotes management (single `'` and double `"`)  
✅ Signal handling (`Ctrl+C`, `Ctrl+\`, `Ctrl+D`)  
✅ Syntax error detection

## 🧠 What I learned
Over and above my technical skills in C and in-depth knowledge of how a UNIX shell works, this project enabled me to develop a number of cross-disciplinary skills:
- *Working in pairs:* code management, constant communication, and shared decision-making on project structure.
- *Organization and rigor:* dividing the project into modules, respecting 42 standards (Norme, Makefile, error management...).
- *Complex problem solving:* management of redirects, pipes, memory, and expected shell behavior, even edge cases.
- *Reading and interpreting system documentation:* understanding and using system calls such as `fork`, `execve`, `dup2`, `waitpid`, etc.
- *Autonomy and perseverance:* facing bugs that were sometimes difficult to debug (particularly 😅 signals), we had to test, search, compare with bash and persist.

## 🧪 Behavior examples
```
$ echo "hello world"
hello world

$ export NAME=Emma
$ echo $NAME
Emma

$ cat fichier.txt | grep "bonjour" > resultat.txt
```

## 📁 Project structure
```
.
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── execution/
│   └── builtins/
├── inc/
│   ├── minishell.h
│   ├── libft/
├── Makefile
└── README.md
```

## 📚 Resources
- Linux `man` pages (`man 3 getenv`, `man 3 execve`, `man 3 signal`, etc...)
- Bash behavior documentation
- `readline` library
- [GConfs - Minishell architecture overview](https://www.youtube.com/watch?v=oIFRiwFRSRY&ab_channel=GConfs)
- [Oceano - Pipex and minishell tips](https://www.youtube.com/watch?v=yTR00r8vBH8&t=415s&ab_channel=Oceano)

## 👨‍💻 Authors
Emma Blanchard  
Akim Hamini
