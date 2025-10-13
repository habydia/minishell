#ifndef PARSING_H
# define PARSING_H

# include "../include/env.h"
# include "../libft/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ========== ENUMS ========== */
typedef struct s_data
{
	char			**dst;
	t_env			*env;
	// t_pars			*pars;
	// t_exec			*exec; type t_cmd
	char			**envp;
	int				errcode;
	int				i;
}					t_data;

// Types de tokens pour le lexer
typedef enum e_token_type
{
	T_WORD,         // mot/commande/argument
	T_PIPE,         // |s
	T_REDIR_IN,     // <
	T_REDIR_OUT,    // >
	T_REDIR_APPEND, // >>
	T_HEREDOC,      // <<
	T_EOF           // fin de ligne
}					t_token_type;

// Types de redirections
typedef enum e_redir_type
{
	R_IN,         // < fichier
	R_OUT_TRUNC,  // > fichier
	R_OUT_APPEND, // >> fichier
	R_HEREDOC     // << delimiteur
}					t_redir_type;

/* ========== STRUCTURES ========== */

// Structure pour un token
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// Structure pour les redirections
typedef struct s_redir
{
	t_redir_type	type;
	char *file; // nom du fichier ou délimiteur heredoc
	struct s_redir	*next;
}					t_redir;

// Structure pour une commande
typedef struct s_cmd
{
	char *name;  // nom de la commande
	char **args; // tableau d'arguments
	char			*path;
	t_redir *redirs;    // liste des redirections
	struct s_cmd *next; // commande suivante (pour pipes)
}					t_cmd;

// typedef struct s_env
// {
// 	char *key;          // HOME
// 	char *value;        // /home/lebroue
// 	struct s_env *next; // On passe a la variable d'env d'apres

// }					t_env;

// Structure pour l'expansion des variables
typedef struct s_expand_data
{
	char			**result;
	size_t			*result_size;
	size_t			*j;
}					t_expand_data;

// Variable globale pour l'exit status
extern int			g_exit_status;

/* ========== FONCTIONS PRINCIPALES ========== */

// init

void				init_data(t_data *data, t_env **envd, char **dst);
// parsing.c - Fonction principale
t_cmd				*parsing(const char *line);

/* ========== LEXER ========== */

// lexer/lexer.c - Fonction principale du lexer
t_token				*line_lexer(const char *line);

// lexer/tokenizer.c - Découpage en tokens
t_token				*tokenize_line(const char *line);
t_token				*create_token(t_token_type type, const char *value);
void				add_token_back(t_token **tokens, t_token *new_token);

// lexer/quote_handler.c - Gestion des guillemets
int					is_quoted_section(const char *str, int start);

// lexer/operator_handler.c - Gestion des opérateurs
t_token_type		get_operator_type(const char *str, int *i);
int					is_operator_char(char c);

/* ========== PARSER ========== */

t_cmd				*parse_tokens(t_token *tokens);
// parser/expander.c - Expansion des variables
t_token				*expand_tokens(t_token *tokens);
int					handle_dollar_sign(const char *line, size_t *i,
						t_expand_data *data);

// parser/expander_utils.c - Fonctions utilitaires pour l'expansion
int					handle_dollar_sign(const char *line, size_t *i,
						t_expand_data *data);

// parser/command_builder.c - Construction des commandes
t_cmd				*build_command(t_token **tokens);
t_cmd				*create_cmd(void);

// parser/pipeline_handler.c - Gestion des pipes
t_cmd				*handle_pipeline(t_token *tokens);

// parser/redirect_handler.c - Gestion des redirections
t_redir				*create_redir(t_redir_type type, const char *file);
void				add_redir_back(t_redir **redirs, t_redir *new_redir);

/* ========== UTILITAIRES ========== */

// Libération mémoire
void				free_tokens(t_token *head);
void				free_cmds(t_cmd *cmds);
void				free_redirs(t_redir *redirs);
void				free_args(char **args);
void				free_args_on_error(char **args);
// Debug (optionnel)
void				print_tokens(t_token *tokens);
void				print_cmds(t_cmd *cmds);

#endif
