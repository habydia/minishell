/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Hadia <Hadia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 20:09:48 by hadia             #+#    #+#             */
/*   Updated: 2025/11/18 16:17:09 by Hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "env.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type	t_token_type;
typedef enum e_redir_type	t_redir_type;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
/* ========== ENUMS ========== */
typedef struct s_env		t_env;
// Types de tokens pour le lexer
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_EOF
}							t_token_type;

// Types de redirections
typedef enum e_redir_type
{
	R_IN,
	R_OUT_TRUNC,
	R_OUT_APPEND,
	R_HEREDOC
}							t_redir_type;

/* ========== STRUCTURES ========== */

// Struct for tokens
typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}							t_token;

// Struct for redirections
typedef struct s_redir
{
	t_redir_type			type;
	char					*file;
	struct s_redir			*next;
}							t_redir;

// Struct for commands
typedef struct s_cmd
{
	char					*name;
	char					*path;
	char					**args;
	t_redir					*redirs;
	struct s_cmd			*next;
}							t_cmd;

// Struct for building arguments
typedef struct s_args_builder
{
	char					**args;
	int						count;
	int						capacity;
	int						skip_first_word;
}							t_args_builder;

// Struct for variable expansion
typedef struct s_expand_data
{
	char					**result;
	size_t					*result_size;
	size_t					*j;
	t_env					*env;
	int						*exit_status;
	int						in_quote;
	char					quote_type;
}							t_expand_data;

/* ========== PRINCIPALES ========== */
char						*ft_getenv(char *name, t_env *envp);
// parsing.c
t_cmd						*parsing(const char *line, t_env *env,
								int *exit_status);

// syntax_checker.c - Syntax validation
int							syntax_errors(t_token *tokens);
/* ========== LEXER ========== */

int							is_quote_balanced(const char *line, int start,
								int end);
int							find_closing_quote(const char *line, int *i,
								char quote_type);
// lexer/lexer.c
t_token						*line_lexer(const char *line);

t_token						*create_token(t_token_type type, const char *value);

// lexer/tokenizer.c
int							add_token_back(t_token **tokens,
								t_token *new_token);
int							push_new_token(t_token **tokens, t_token_type type,
								char *value);
t_token						*tokenize_line(const char *line);
// utils_tokenizer.c - utils

int							tokenize_operator(const char *line, int *i,
								int *start, t_token **tokens);

int							tokenize_quote(const char *line, int *start, int *i,
								t_token **tokens);

int							tokenize_word(int *start, int *i, t_token **tokens,
								const char *line);
int							handle_quote(const char *line, int *i, int *start,
								t_token **tokens);

int							handle_operator_and_quote(int *i, int *start,
								const char *line, t_token **tokens);

// lexer/operator_handler.c - operators Gestion
t_token_type				get_operator_type(const char *str, int *i);
int							is_operator_char(char c);

/* ========== PARSER ========== */

t_cmd						*parse_tokens(t_token *tokens);
// parser/expander.c - variables Expansion
t_token						*expand_tokens(t_token *tokens, t_env *env,
								int *exit_status);
int							handle_dollar_sign(const char *line, size_t *i,
								t_expand_data *data);
int							ft_count_quotes(const char *str);
char						*remove_quotes(const char *value, char quote_type);
// parser/expander_utils.c - utils for expansion
char						*process_token_expansion(const char *value,
								t_env *env, int *exit_status);
t_token						*remove_empty_tokens(t_token *tokens);
// parser/command_builder.c - building Commands
int							build_redirection_token(t_token **current,
								t_cmd *cmd);
t_cmd						*build_command(t_token **tokens);
t_cmd						*create_cmd(void);
t_redir						*create_redir(t_redir_type type, const char *file);

// parser/pipeline_handler.c - pipes Gestion
t_cmd						*handle_pipeline(t_token *tokens);
void						handle_heredoc(t_redir *redir);

// parser/redirect_handler.c - redirections Gestion
void						add_redir_back(t_redir **redirs,
								t_redir *new_redir);

// utils_command_builder.c - utils for command building
int							handle_word_token(t_args_builder *builder,
								const char *value);
int							handle_token(t_token **current, t_cmd *cmd,
								t_args_builder *builder);
int							process_tokens(t_token **tokens, t_cmd *cmd,
								char ***args, int *arg_count);
char						**init_args_array(const char *cmd_name,
								int *capacity);

/* ========== UTILITAIRES ========== */

// Memory Management
void						free_tokens(t_token *head);
void						free_redirs(t_redir *redirs);
void						free_args_on_error(char **args);
#endif
