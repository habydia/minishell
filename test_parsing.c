#include "include/parsing.h"

/*
 * Affiche une commande pour debug
 */
void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;
	char	*redir_names[] = {"<", ">", ">>", "<<"};

	if (!cmd)
		return;
	
	printf("=== COMMAND ===\n");
	printf("Name: %s\n", cmd->name ? cmd->name : "NULL");
	
	printf("Args: ");
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
	
	printf("Redirections: ");
	redir = cmd->redirs;
	while (redir)
	{
		printf("(%s %s) ", redir_names[redir->type], redir->file);
		redir = redir->next;
	}
	printf("\n");
	
	if (cmd->next)
		printf("Next: -> (pipe)\n");
	else
		printf("Next: NULL\n");
	
	printf("===============\n\n");
}

/*
 * Affiche toutes les commandes
 */
void	print_all_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;

	current = cmds;
	i = 1;
	
	printf("\n=== PARSING RESULT ===\n");
	while (current)
	{
		printf("Command %d:\n", i);
		print_cmd(current);
		current = current->next;
		i++;
	}
	printf("======================\n\n");
}

/*
 * Test une ligne de commande
 */
void	test_line(const char *line)
{
	t_cmd	*cmds;

	printf("Testing: \"%s\"\n", line);
	printf("-" "--------------------\n");
	
	cmds = parsing(line);
	if (cmds)
	{
		print_all_cmds(cmds);
		free_cmds(cmds);
	}
	else
	{
		printf("Parsing failed!\n\n");
	}
}

/*
 * Fonction principale de test
 */
int	main(int argc, char **argv)
{

	if (argc < 2)
	{
		printf("Usage: %s \"command line\"\n", argv[0]);
		return (1);
	}
	else if (argc == 2)
	{
		test_line(argv[1]);

	}
	// printf("=== MINISHELL PARSER TEST ===\n\n");
	
	// // Tests simples
	// test_line("echo hello");
	// test_line("ls -la");
	// test_line("cat file.txt");

	// //tests avec variables 
	// test_line("echo $USER");
	// // test_line("echo \$USER\"");

	// // Tests avec guillemets
	// test_line("echo \"hello world\"");
	// test_line("echo 'single quotes'");

	// //test $
	// 	test_line("echo $USER");
	// 	test_line("echo '$USER'");
	// 	test_line("echo \"\\$USER\"");
	
	// // Tests avec redirections
	// test_line("echo hello > output.txt");
	// test_line("cat < input.txt");
	// test_line("echo hello >> append.txt");
	// test_line("cat << EOF");
	
	// // Tests avec pipes
	// test_line("ls | grep txt");
	// test_line("cat file | head -5 | tail -2 | tail -2");
	
	// // Tests complexes
	// test_line("echo \"hello world\" hvby | grep hello > output.txt");
	// test_line("ls -la | grep \".txt\" >> results.txt");
	
	// printf("=== END OF TESTS ===\n");
	return (0);
}
