
Résumé des modules et priorités :

1. Module Parsing : Analyse et découpage des commandes.
2. Module Builtins : Implémentation des builtins (cd, echo, etc.).
3. Module Execution : Gestion des pipes, redirections et execve().
4. Module Signaux : Gérer les interruptions (Ctrl+C, etc.).
5. Module Environnement : Gestion des variables d'environnement


Explication de chaque fonction et de son prototype :

---

### **Fonctions associées à `readline`** :
1. **`readline(const char *prompt)`**
   - Lit une ligne de texte à partir de l'entrée standard avec une invite spécifiée (et gère l'historique automatiquement).

2. **`rl_clear_history(void)`**
   - Efface tout l'historique de commandes précédemment stocké.

3. **`rl_on_new_line(void)`**
   - Indique à la bibliothèque `readline` que l'utilisateur interagit sur une nouvelle ligne.

4. **`rl_replace_line(const char *text, int clear_undo)`**
   - Remplace le contenu actuel de la ligne dans le buffer par un texte donné.

5. **`rl_redisplay(void)`**
   - Réaffiche l’invite (`prompt`) et la ligne courante (utile après une interruption).

6. **`add_history(const char *line)`**
   - Ajoute une commande dans l’historique des commandes.

---

### **Fonctions de gestion d'entrée/sortie classiques** :
7. **`printf(const char *format, ...)`**
   - Imprime un texte formaté sur la sortie standard (`stdout`).

8. **`write(int fd, const void *buf, size_t count)`**
   - Écrit `count` octets du buffer `buf` dans le fichier ou flux référencé par `fd`.

9. **`read(int fd, void *buf, size_t count)`**
   - Lit jusqu'à `count` octets depuis le descripteur de fichier `fd` dans le buffer `buf`.

10. **`access(const char *pathname, int mode)`**
    - Vérifie l'accès au fichier (par exemple : existence, permission d'écriture/lecture/exécution).

11. **`open(const char *pathname, int flags, ...)`**
    - Ouvre un fichier ou crée un nouveau fichier, selon les `flags`.

12. **`close(int fd)`**
    - Ferme un descripteur de fichier ouvert.

13. **`unlink(const char *pathname)`**
    - Supprime (délie) un fichier donné (ne supprime son contenu qu’après que tous les processus referment ce fichier).

---

### **Fonctions de gestion mémoire** :
14. **`malloc(size_t size)`**
    - Alloue un bloc de mémoire de `size` octets et retourne un pointeur dessus.

15. **`free(void *ptr)`**
    - Libère un bloc de mémoire préalablement alloué par `malloc`.

---

### **Fonctions liées au processus** :
16. **`fork(void)`**
    - Crée un nouveau processus (fils) en dupliquant le processus père.

17. **`wait(int *wstatus)`**
    - Attend la fin d’un processus enfant et récupère son statut.

18. **`waitpid(pid_t pid, int *wstatus, int options)`**
    - Attend la fin d’un processus spécifique (identifié par son `pid`).

19. **`wait3(int *wstatus, int options, struct rusage *rusage)`**
    - Attend la terminaison d’un processus enfant et collecte en plus des statistiques de ressources.

20. **`wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)`**
    - Similaire à `wait3`, mais permet de spécifier un `pid` précis.

21. **`kill(pid_t pid, int sig)`**
    - Envoie un signal donné (`sig`) à un processus ou un groupe de processus identifié par `pid`.

22. **`exit(int status)`**
    - Termine le processus en cours et retourne un `status` au système.

---

### **Fonctions de gestion des signaux** :
23. **`signal(int signum, sighandler_t handler)`**
    - Définit une action personnalisée ou par défaut pour un signal particulier.

24. **`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**
    - Configure une gestion avancée des signaux, en remplaçant l'ancienne méthode `signal`.

25. **`sigemptyset(sigset_t *set)`**
    - Initialise un ensemble de signaux donné (vide).

26. **`sigaddset(sigset_t *set, int signum)`**
    - Ajoute un signal spécifique dans un ensemble de signaux.

---

### **Fonctions de gestion de fichiers et répertoires** :
27. **`getcwd(char *buf, size_t size)`**
    - Obtient le chemin absolu du répertoire courant (affiché dans `buf`).

28. **`chdir(const char *path)`**
    - Change le répertoire de travail actuel vers le chemin spécifié.

29. **`stat(const char *path, struct stat *buf)`**
    - Récupère les informations sur un fichier ou un répertoire (taille, permissions, etc.).

30. **`lstat(const char *path, struct stat *buf)`**
    - Semblable à `stat`, mais ne suit pas les liens symboliques.

31. **`fstat(int fd, struct stat *buf)`**
    - Récupère les informations sur un fichier via son descripteur de fichier ouvert (`fd`).

32. **`unlink(const char *pathname)`**
    - Supprime un fichier donné.

33. **`opendir(const char *name)`**
    - Ouvre un répertoire et retourne un pointeur vers cet objet.

34. **`readdir(DIR *dirp)`**
    - Retourne une entrée de répertoire depuis un objet de type `DIR` (lecture d’un dossier).

35. **`closedir(DIR *dirp)`**
    - Ferme un descripteur de répertoire ouvert.

---

### **Fonctions liées à l’exécution de programmes externes** :
36. **`execve(const char *pathname, char *const argv[], char *const envp[])`**
    - Exécute un programme externe en remplaçant complètement l’espace mémoire courant.

37. **`dup(int oldfd)`**
    - Duplique un descripteur de fichier.

38. **`dup2(int oldfd, int newfd)`**
    - Duplique un descripteur dans un autre (utile pour redirections).

39. **`pipe(int pipefd[2])`**
    - Crée un canal de communication entre deux processus (un descripteur pour lire, un autre pour écrire).

---

### **Fonctions liées à la gestion des erreurs** :
40. **`strerror(int errnum)`**
    - Retourne le message d’erreur associé à un numéro d’erreur donné (`errno`).

41. **`perror(const char *s)`**
    - Affiche un message d'erreur sur la sortie standard d'erreur (`stderr`), suivi de l'explication de l'erreur courante.

---

### **Fonctions liées à l'entrée standard et terminaux** :
42. **`isatty(int fd)`**
    - Vérifie si un descripteur de fichier fait référence à un terminal.

43. **`ttyname(int fd)`**
    - Retourne le nom du fichier de terminal associé à un descripteur donné.

44. **`ttyslot(void)`**
    - Récupère l'index de l'entrée associée au terminal actuel dans le fichier `/etc/ttys`.

45. **`ioctl(int fd, unsigned long request, ...)`**
    - Configure ou contrôle le périphérique spécifié par un descripteur de fichier (notamment les terminaux).

---

### **Fonctions de gestion des variables d'environnement** :
46. **`getenv(const char *name)`**
    - Récupère la valeur d'une variable d’environnement (par exemple, `PATH`).

47. **`tcsetattr(int fd, int optional_actions, struct termios *termios_p)`**
    - Configure les attributs du terminal.

48. **`tcgetattr(int fd, struct termios *termios_p)`**
    - Récupère les attributs du terminal.

---

### **Fonctions liées aux capacités du terminal** :
49. **`tgetent(char *bp, const char *name)`**
    - Initialise les capacités du terminal pour un terminal donné.

50. **`tgetflag(const char *id)`**
    - Vérifie si une capacité numérique est activée sur le terminal.

51. **`tgetnum(const char *id)`**
    - Récupère la valeur d'une capacité numérique pour un terminal donné.

52. **`tgetstr(const char *id, char **area)`**
    - Récupère les chaînes de contrôle associées à une capacité terminal donnée.

53. **`tgoto(const char *cap, int col, int row)`**
    - Construit une séquence de positionnement de curseur pour un terminal donné.

54. **`tputs(const char *str, int affcnt, int (*putc)(int))`**
    - Écrit une chaîne de contrôle pour un terminal en utilisant une fonction personnalisée `putc`.

---