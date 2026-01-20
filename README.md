*This project has been created as part of the 42 curriculum by nfiora-d.*

---

# Pipex

## Description

Le projet **Pipex** a pour objectif de reproduire le fonctionnement du pipe sous Unix en C. Il permet de comprendre en profondeur la manipulation des fd, les redirections et la communication entre processus.

Le programme exécute la commande comme dans le shell :
`< file1 cmd1 | cmd2 > file2`

Il prend 4 arguments :
1. **file1** : Le fichier d'entrée (input).
2. **cmd1** : La première commande shell (avec ses paramètres).
3. **cmd2** : La deuxième commande shell (avec ses paramètres).
4. **file2** : Le fichier de sortie (output).

L'exécution crée un mécanisme reliant la sortie standard de la première commande à l'entrée standard de la seconde via un pipe.

---

## Instructions

Pour run le programme faire comme dans l'exemple
`< file1 cmd1 | cmd2 > file2`

### Prérequis
* **OS** : Linux ou macOS
* **Compilateur** : cc
* **Outils** : make

### Compilation
Pour compiler le programme, exécutez la commande suivante à la racine du projet :

make