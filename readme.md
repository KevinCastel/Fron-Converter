# Objectif de l'application
L'application permet de convertir un élément HTML avec son style CSS en JavaScript.
Le style CSS est optionnel, cependant, si l'identifiant de l'élément n'est pas trouvé mais que le style a été précisé.
La recherche va se faire par :
- **Soit par la Classe**
- **Soit par le type de l'élément**

# Utilisation
## Lancement de l'application compilé
### Par Console
  1. **Ouvrir le terminal** avec `CTRL` + `ALT` + `T`
  2. **Naviguer jusqu'au répertoire du projet** `chemin/vers/HTMLCSS-TO-JS/`
  3. **Taper la commande** `./app <html_file> <node_to_find> <css_file>` :
      - **html_file** représente le chemin du fichier HTML à explorer
      - **node_to_find** représente l'élément à trouver dans le fichier HTML :
          - **Par défaut, un identifiant (id) est attendu**
          - Sinon, on peut préciser le sélecteur de la manière suivante : `<selector='selector'>`
          - **Voici les sélecteurs disponibles** :
              * id
              * class
              * élément type
      - **css_file** représente le chemin du fichier CSS

## Compilation
- Après modification du script [main.c](./main.c), il est nécessaire de recompiler le programme à l'aide du paquet `gcc`.
Si vous n'avez pas encore installer le `paquet gcc`.

### Installation du paquet `gcc`
Pour installer, il vous faudra suivre les étapes suivante :
    1. **apt-get update** (pour les mises à jour de la maintenance)
    2. **apt-get upgrade** (pour les mises à jour de la maintenance)
    3. **apt-get install gcc** (pour installer les `paquets du GNU` (`Compiler Collection pour le C, C++`))
    4. **gcc --version** (pour vérifier que le paquet est bien installé)

### Compilation du programme
Il existe plusieurs manières pour compiler un programme en `C` depuis le `paquet gcc`.
La compilation sera compilé depuis l'outil `MakeFile` en utilisant des règles écrite dans ce `MakeFile`.
Le `MakeFile`est fournis, il est automatisé. Vous devez l'"executer" pour recompiler l'application avec les 
commandes suivante:
    1. **Ouvrer un terminal avec le raccourci clavier** `CTRL`+`ALT`+`T` 
    2. **Naviguer jusqu'au répertoire du projet** `chemin/vers/HTMLCSS-TO-JS`
    3. **Compiler avec la commande** `make`

### Lancement de l'application
Une fois la compilation terminée, vous pouvez lancer l'application avec les manipulations suivante:
    1. **Ouvrer un terminal avec le raccourci clavier** `CTRL`+`ALT`+`T`
    2. **Naviguer jusqu'au répertoire du projet** `chemin/vers/HTMLCSS-TO-JS`
    3. **Lancer l'application avec la commande suivante** `./bin/app`
