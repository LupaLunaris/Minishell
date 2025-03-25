
// On test ici la partie parsing
// considerant que nous avons un array comprenant des *char
// l'expression "cat < input.txt | grep test > output.txt:" dans le prompt
// devient splited_args = {"cat","<", "input.txt" "|" "grep" "test" ">" "output.txt"}
// ceci sera fait dans la partie lexing.

// le parsing operer ici stock les informations du prompt dans une liste chainee de commandes *t_cdm.

// si redirection < > << >>
// 	 on stocke ce qui suit la redirection dans le node t_cdm courant
//  echo "bla" > test.txt
// cdm->args = {"echo", "bla"}
// cdm->output_file = test.txt

// si pipe, a chaque pipe on avance dans la liste t_cdm et on recommence
// jusqua avoir autant de noeud qu'il y a de commande de chaque coter des pipe (nb pipe +1)
// 1 | 2 | 3 .


// l'idee est que pour chaque commandes on stocke le ou les fd neccessaire.
// pour le moment c'est un *char file
// je suppose que c'est ammener a devenir une struct
// avec pid du fork ? , fd, *char filename ...
// ...  ou pas ! en verifiant par exemple if(cdm->intput_file) tu as peut etre les info suffisante ...
// ... pour traiter avec cdm->output_file ou cdm->pipe_next->args

// les deux premiere fonction sont juste pour imprimer le contenu de la liste.

#include "../../includes/minishell.h"
void    print_cmd(t_cmd *cmd)
{
    int i;

    printf("\n--- Nouvelle commande ---\n");
    printf("Arguments : ");
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            printf("[%s] ", cmd->args[i]);
            i++;
        }
    }
    printf("\n");

	if (cmd->cmd)
		printf("commande : %s\n", cmd->cmd);
	if (cmd->builtin)
		printf("%s : est un builtin\n", cmd->cmd);
    if (cmd->input_file)
        printf("Input file: %s\n", cmd->input_file);
    if (cmd->output_file)
        printf("Output file%s\n", cmd->output_file);
    if (cmd->append)
        printf("il faut append %s\n", cmd->output_file);
    if (cmd->heredoc)
        printf("Heredoc delimiter: %s\n", cmd->heredoc);
}

// Fonction utilitaire pour afficher toute la liste de commandes
void    print_cmd_list(t_cmd *head)
{
    t_cmd *current;
    int   cmd_num;

    current = head;
    cmd_num = 1;
    while (current)
    {
        printf("\nCommande #%d:", cmd_num++);
        print_cmd(current);
        current = current->pipe_next;
    }
    printf("\n");
}
int main(void)
{

	// Test 1: Commande simple
    printf("\nTest 1: ls -la\n");
    char *test1[] = {"ls", "-la", NULL};
    t_cmd *result1 = parser(test1);
	add_builtin(result1);
    print_cmd_list(result1);
    clean_cmd_list(result1);

    // Test 2: Commande avec redirection
    printf("\nTest 2: echo coucou > output.txt\n");
    char *test2[] = {"echo", "coucou", ">", "output.txt", NULL};
    t_cmd *result2 = parser(test2);
	add_builtin(result2);
    print_cmd_list(result2);
    clean_cmd_list(result2);

    // Test 3: Commande avec pipe
    printf("\nTest 3: ls -la | grep test\n");
    char *test3[] = {"ls", "-la", "|", "grep", "test", NULL};
    t_cmd *result3 = parser(test3);
	add_builtin(result3);
    print_cmd_list(result3);
    clean_cmd_list(result3);

    // Test 4: Commande complexe
    printf("\nTest 4: cat < input.txt | grep test > output.txt | grep, test, > output.txt | grep, test, > output.txt\n");
    char *test4[] = {"cat", "<", "input.txt", "|", "pwd", ">", "output.txt", "|", "grep", "test", ">", "output.txt", NULL};
    t_cmd *result4 = parser(test4);
	add_builtin(result4);
    print_cmd_list(result4);
    clean_cmd_list(result4);

    // Test 5: Commande avec heredoc
    printf("\nTest 5: cat << EOF | grep test >> output.txt\n");
    char *test5[] = {"cat", "<<", "EOF", "|", "grep", "test", ">>", "output.txt", NULL};
    t_cmd *result5 = parser(test5);
	add_builtin(result5);
    print_cmd_list(result5);
    clean_cmd_list(result5);

    return (0);
}