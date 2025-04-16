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
Au-delà des compétences techniques en C et de la connaissance approfondie du fonctionnement d’un shell UNIX, ce projet m’a permis de développer de nombreuses compétences transversales :
- *Travail en binôme :* gestion du code à deux, communication constante, et prise de décision partagée sur la structure du projet.
- *Organisation et rigueur :* découpage du projet en modules, respect des normes 42 (Norme, Makefile, gestion des erreurs...).
- *Résolution de problèmes complexes :* gestion des redirections, des pipes, de la mémoire, et du comportement attendu d’un shell, même dans des cas limites.
- *Lecture et interprétation de documentation système :* pour comprendre et utiliser des appels système comme fork, execve, dup2, waitpid, etc.
- *Autonomie et persévérance :* face aux bugs parfois difficiles à déboguer (notamment les signaux 😅), il a fallu tester, chercher, comparer avec bash et persister.

## 🧪 Examples
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
