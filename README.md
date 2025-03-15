# 🐚 Minishell
Un projet réalisé dans le cadre du cursus à l'école 42, en binôme avec Akim 👥  
Ce projet a pour but de recréer un shell Unix minimaliste en langage C, capable d’interpréter et d’exécuter des commandes de manière interactive.

# 🚀 Objectif du projet
👉 Apprendre à gérer des processus, des signaux et des entrées/sorties.  
👉 Reproduire certaines fonctionnalités du shell Bash.  
👉 Implémenter un interpréteur de commandes robustes, gérant les redirections, pipes, variables d’environnement...  

# 🛠️ Fonctionnalités
- Exécution de commandes (simples et avec chemins absolus/relatifs)
- Commandes built-in : echo, cd, pwd, export, unset, env, exit
- Redirections : >, >>, <, <<
- Pipes (|) entre plusieurs commandes
- Gestion des variables d’environnement ($USER, etc.)
- Gestion des signaux (Ctrl+C, Ctrl+D, etc.)
- Gestion des quotes simples et doubles
- Retour du code de sortie dans $?
- Analyse syntaxique et protection contre les erreurs

# 🧪 Exemples d'utilisation
```
$ echo "hello world"
hello world

$ export NAME=Emma
$ echo $NAME
Emma

$ cat fichier.txt | grep "bonjour" > resultat.txt
```

# 👨‍💻 Développeurs
Emma Blanchard  
Akim Hamini

# 📁 Structure du projet
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

# 📚 Ressources utilisées
- man pages : man 3 getenv, man 3 execve, man 3 signal...
- Bash documentation pour les comportements à reproduire
- MiniLibC, readline
- https://www.youtube.com/watch?v=oIFRiwFRSRY&ab_channel=GConfs
- https://www.youtube.com/watch?v=yTR00r8vBH8&t=415s&ab_channel=Oceano
