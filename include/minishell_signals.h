/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:16:53 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 15:47:33 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include "../libft/libft.h"
# include "env.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal_status;

# define SIG_NONE 0
# define SIG_INTERRUPTED 1
# define SIG_HEREDOC_INTERRUPTED 2

typedef struct s_redir			t_redir;
//
/* **********************************SIGNALS***************************** */
void							setup_sigint(void);
void							setup_sigquit(void);
void							handle_sigint(int sig);
void							handle_signals(void);
void							ignore_sigint_in_parent(void);

char							*reader(t_data *data);

//
/* **************************HEREDOC SIGNALS****************************** */
void							handle_sigint_heredoc(int sig);
void							setup_sigint_heredoc(void);
void							apply_ctrld(char const *delimiter);
void							apply_handle_signals(char *line,
									int stdin_backup);
void							handle_heredoc_error(t_redir *redir,
									char *temp_filename, char *delimiter,
									int fd);
#endif /* MINISHELL_SIGNALS_H */