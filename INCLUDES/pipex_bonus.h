/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:03:05 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 15:46:04 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <errno.h>

typedef struct pipexu
{
	int		pip[2];
	pid_t	id;
	char	**args;
	char	*path;
	int		i;
	int		cmdn;
}	t_pipexu;

void	pipex(int *fd_io, char **av, char **env, int cmdn);
char	*ft_getenv(char **env);
void	ft_error(char *s);
char	*check_cmd_path(char **env, char *cmd);
void	ft_free2(char **string);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strjoin(char *dst, char *src);
void	ft_exitstatus(int status, int i, int cmdn);
void	ft_child(int *fd_io, t_pipexu uts, char **av, char **env);

#endif
