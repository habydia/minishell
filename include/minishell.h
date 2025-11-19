/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 03:28:45 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 00:20:38 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "env.h"
# include "exec.h"
# include "ft_free.h"
# include "minishell_signals.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h> // open()
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h> // malloc, free
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h> // c

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

#endif /* MINISHELL_H */