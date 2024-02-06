# 42-webserv

## Installation


### `make`

Build l'application.

### `./server`

Lance le programme avec le fichier de configuration par défaut.

Le fichier de configuration par défaut se trouve ici : `./config/default.conf`. Si vous voulez personnaliser la configuration du serveur, privilégiez la création d'un fichier de configuration séparé.

### `./server ./path/to/conf`

Lance le serveur avec un fichier de configuration spécifique.

## Structure

```ini
config      # fichiers de configuration du serveur
html        # dossier du serveur de test
includes    # fichiers .hpp
srcs        # fichiers .cpp
test        # fichiers de configuration test
```

## Credit

@[Dai Clément (cdai)](https://github.com/DaiClement)<br>
@[Mazoise (mchardin)](https://github.com/Mazoise)<br>
@[Syndraum (roalvare)](https://github.com/Syndraum)