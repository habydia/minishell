#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include "../libft/libft/libft.h"
# include "env.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

extern int						g_exit_status;
extern volatile sig_atomic_t	g_interrupted;
extern volatile sig_atomic_t	g_heredoc_interrupted;

typedef struct s_redir			t_redir;
//
/* **********************************SIGNALS**************************************** */
void							setup_sigint(void);
void							setup_sigquit(void);
void							handle_sigint(int sig);
void							handle_signals(void);

char							*reader(t_data *data);

//
/* **************************HEREDOC SIGNALS*************************************** */
void							handle_sigint_heredoc(int sig);
void							setup_sigint_heredoc(void);
void							apply_ctrld(char const *delimiter);
void							apply_handle_signals(char *line,
									int stdin_backup);
void							handle_heredoc_error(t_redir *redir,
									char *temp_filename, char *delimiter,
									int fd);
#endif /* MINISHELL_SIGNALS_H */