# 🐚 Minishell
Un projet réalisé dans le cadre du cursus à l'école 42, en binôme avec Akim 👥  
Ce projet a pour but de recréer un shell Unix minimaliste en langage C, capable d’interpréter et d’exécuter des commandes de manière interactive.

# 🚀 Objectif du projet
👉 Apprendre à gérer des processus, des signaux et des entrées/sorties.  
👉 Reproduire certaines fonctionnalités du shell Bash.  
👉 Implémenter un interpréteur de commandes robustes, gérant les redirections, pipes, variables d’environnement...  

# 🧠 Ce que ce projet m’a appris
Au-delà des compétences techniques en C et de la connaissance approfondie du fonctionnement d’un shell UNIX, ce projet m’a permis de développer de nombreuses compétences transversales :
- *Travail en binôme :* gestion du code à deux, communication constante, et prise de décision partagée sur la structure du projet.
- *Organisation et rigueur :* découpage du projet en modules, respect des normes 42 (Norme, Makefile, gestion des erreurs...).
- *Résolution de problèmes complexes :* gestion des redirections, des pipes, de la mémoire, et du comportement attendu d’un shell, même dans des cas limites.
- *Lecture et interprétation de documentation système :* pour comprendre et utiliser des appels système comme fork, execve, dup2, waitpid, etc.
- *Autonomie et persévérance :* face aux bugs parfois difficiles à déboguer (notamment les signaux 😅), il a fallu tester, chercher, comparer avec bash et persister.

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
