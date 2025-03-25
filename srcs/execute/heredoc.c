
#include "minishell.h"

typedef struct s_custom_file
{
    int fd;           // Descripteur de fichier
    char buffer[1024]; // Buffer de lecture
    int position;     // Position dans le buffer
    int size;         // Taille des données dans le buffer
    int eof;          // Indicateur de fin de fichier
} t_custom_file;

/**
 * Crée un fichier temporaire et y écrit le contenu
 * @param content Contenu à écrire
 * @return Descripteur de fichier ou -1
 */
int create_temp_with_content(const char *content)
{
    int fd;
    int i;
    char template[] = "/tmp/temp_XXXXXX";

    fd = open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd < 0)
        return (-1);
    i = 0;
    while (content[i])
        i++;
    if (write(fd, content, i) < 0)
    {
        close(fd);
        unlink(template);
        return (-1);
    }
    // Repositionnement au début du fichier
    close(fd);
    fd = open(template, O_RDWR);
    unlink(template); // Supprime le fichier mais garde le descripteur valide

    return (fd);
}

/**
 * Initialise notre structure custom_file
 * @param content Contenu à mettre dans le fichier
 * @return Structure initialisée ou NULL
 */
t_custom_file *custom_string_to_file(const char *content)
{
    t_custom_file *file;
    int fd;

    if (!content)
        return (NULL);
    fd = create_temp_with_content(content);
    if (fd < 0)
        return (NULL);
    file = (t_custom_file *)malloc(sizeof(t_custom_file));
    if (!file)
    {
        close(fd);
        return (NULL);
    }
    file->fd = fd;
    file->position = 0;
    file->size = 0;
    file->eof = 0;

    return (file);
}

/**
 * Lit des données depuis notre structure custom
 * @param file Structure personnalisée
 * @param buffer Buffer où stocker les données
 * @param size Taille maximale à lire
 * @return Nombre d'octets lus ou -1
 */
int custom_read(t_custom_file *file, void *buffer, int size)
{
    int bytes_read;

    if (!file || file->fd < 0 || !buffer || size <= 0)
        return (-1);

    bytes_read = read(file->fd, buffer, size);
    return (bytes_read);
}

/**
 * Ferme et libère la structure personnalisée
 * @param file Structure à fermer
 */
void custom_close(t_custom_file *file)
{
    if (file)
    {
        if (file->fd >= 0)
            close(file->fd);
        free(file);
    }
}
