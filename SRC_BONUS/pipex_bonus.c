/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:35:47 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 01:10:32 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/pipex_bonus.h"

void	pipex(int *fd_io, char **av, char **env, int cmdn)
{
	t_pipexu	uts;
	int			status;

	uts.i = 2;
	uts.cmdn = cmdn;
	while (uts.i < cmdn)
	{
		if (pipe(uts.pip) == -1)
			exit(EXIT_FAILURE);
		uts.id = fork();
		if (uts.id == -1)
			exit(EXIT_FAILURE);
		if (!uts.id)
			ft_child(fd_io, uts, av, env);
		close(uts.pip[1]);
		if (uts.i == 2)
			close(fd_io[0]);
		fd_io[0] = uts.pip[0];
		(uts.i)++;
	}
	waitpid(uts.id,&status,0);
	ft_exitstatus(satus, uts.i, cmdn);
}

void	ft_child(int *fd_io, t_pipexu uts, char **av, char **env)
{
	if (fd_io[0] < 0)
		exit(EXIT_FAILURE);
	close(uts.pip[0]);
	dup2(fd_io[0], 0);
	close (fd_io[0]);
	if (uts.i == (uts.cmdn - 1))
	{
		dup2(fd_io[1], 1);
		close(fd_io[1]);
	}
	else
	{
		dup2(uts.pip[1], 1);
		close(uts.pip[1]);
	}
	uts.args = ft_split(av[uts.i], ' ');
	if (!uts.args)
		exit(EXIT_FAILURE);
	uts.path = check_cmd_path(env, uts.args[0]);
	if (!uts.path)
		ft_error(uts.args[0]);
	execve(uts.path, uts.args, env);
	exit(EXIT_FAILURE);
}

void	ft_error(char *s)
{
	ft_putstr_fd(s, 2);
	if (errno != 13)
	{
		ft_putstr_fd(":command not found\n", 2);
		exit(127);
	}
	perror("");
	exit(126);
}

void	ft_exitstatus(int status, int i, int cmdn)
{
	int	exitstatus;

	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
		if (exitstatus && (cmdn - 1) == i)
			exit(exitstatus);
	}
}
