

Résumé du lexing dans Minishell
Objectif du lexing
Le lexing est la première étape du traitement des commandes dans notre shell. Son rôle est de transformer l'entrée brute de l'utilisateur en une séquence de tokens typés qui seront ensuite interprétés par le parser.
Ce que notre lexer produit
Notre lexer prend une chaîne de caractères (la commande entrée par l'utilisateur) et renvoie une liste chaînée de tokens. Chaque token contient:

Une valeur textuelle (value)
Un type qui identifie sa nature (type)
Un pointeur vers le token suivant (next)

Les types de tokens produits sont:

TOKEN_WORD: pour les commandes, arguments, et autres mots
TOKEN_PIPE: pour les pipes (|)
TOKEN_REDIR_IN: pour les redirections d'entrée (<)
TOKEN_REDIR_OUT: pour les redirections de sortie (>)
TOKEN_APPEND: pour les redirections d'ajout (>>)
TOKEN_HEREDOC: pour les heredocs (<<)
TOKEN_ERROR: pour signaler une erreur de syntaxe (ex: guillemet non fermé)

Pourquoi cette conception
Cette approche permet:

Séparation des responsabilités: Le lexer se concentre uniquement sur la tokenisation sans interprétation, tandis que les étapes ultérieures (parsing, expansion) s'occupent de donner un sens à ces tokens.
Préservation du contexte: Les guillemets et les caractères d'échappement sont conservés dans les tokens pour permettre une interprétation correcte plus tard.
Identification claire des opérateurs: Les redirections et pipes sont identifiés comme des tokens spécifiques, facilitant la construction de l'arbre syntaxique.

Comment notre lexer fonctionne
Notre lexer utilise une approche par machine à états:

État normal (STATE_NORMAL): traite les caractères normaux, espaces, opérateurs et guillemets
État guillemet simple (STATE_IN_SQUOTE): traite les caractères à l'intérieur de guillemets simples
État guillemet double (STATE_IN_DQUOTE): traite les caractères à l'intérieur de guillemets doubles

Le lexer parcourt la chaîne caractère par caractère et, selon l'état courant:

Identifie les limites des tokens (espaces, opérateurs)
Conserve les guillemets et leur contenu
Détecte les opérateurs de redirection et les pipes
Vérifie la cohérence syntaxique (ex: guillemets fermés)

Comment notre lexer répond aux exigences

Gestion des cas complexes:

hello'world' est correctement traité comme un seul token
echo " ' '$USER' '"$USER"' ''''$$'''' ' " est correctement tokenisé avec préservation des guillemets


Guillemets et espaces:

Les espaces hors guillemets délimitent les tokens
Les espaces dans les guillemets sont préservés
Les guillemets sont conservés pour l'interprétation ultérieure


Variables et expansions:

Les variables comme $USER et $? sont préservées dans les tokens
L'expansion sera effectuée ultérieurement, en respectant le contexte des guillemets


Redirections et pipes:

Les opérateurs sont correctement identifiés
Les redirections complexes comme <<, >> sont traitées comme des tokens distincts


Détection d'erreurs:

Les guillemets non fermés sont détectés et signalés



Relation avec l'étape suivante (parsing)
Le parser utilisera ces tokens typés pour:

Construire un arbre de commandes (commandes simples, pipes, redirections)
Vérifier la syntaxe (par exemple, s'assurer qu'une redirection est suivie d'un nom de fichier)
Préparer les structures de données pour l'exécution

Notre conception du lexer facilite ce travail en:

Identifiant clairement les éléments syntaxiques
Préservant toutes les informations nécessaires à l'interprétation correcte
Signalant les erreurs de syntaxe de base

Cette approche modulaire rend le shell plus robuste et plus facile à maintenir, tout en permettant de traiter correctement les cas complexes requis par la norme POSIX