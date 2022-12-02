/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:03:05 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 01:03:36 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <errno.h>

typedef struct idlist
{
	char	**args;
	char	*path;
}	t_idcmd;

void	pipex(int *fd_io, char **av, char **env);
char	*ft_getenv(char **env);
void	ft_error(char *s);
char	*check_cmd_path(char **env, char *cmd);
void	ft_free2(char **string);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strjoin(char *dst, char *src);
void	ft_child2process(int *fd, int *fd_inout, char **av, char **env);
void	ft_child1process(int *fd, int *fd_inout, char **av, char **env);
void	ft_exitstatus(int status);

#endif
