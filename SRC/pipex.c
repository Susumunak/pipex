/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:01:56 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 01:09:36 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/pipex.h"

void	pipex(int *fd_io, char **av, char **env)
{
	int		pip[2];
	int		status;
	pid_t	id[2];

	if (pipe(pip) == -1)
		return (perror("couldn't pipe:"));
	id[0] = fork();
	if (id[0] == -1)
		return (perror("couldn't fork:"));
	if (!id[0])
		ft_child1process(pip, fd_io, av, env);
	id[1] = fork();
	if (id[1] == -1)
		return (perror("couldn't fork 2:"));
	if (!id[1])
		ft_child2process(pip, fd_io, av, env);
	close(pip[0]);
	close(pip[1]);
	waitpid(id[0], NULL, 0);
	waitpid(id[1], &status, 0);
	ft_exitstatus(status);
}

void	ft_child1process(int *fd, int *fd_inout, char **av, char **env)
{
	t_idcmd	cmd1;

	cmd1.args = ft_split(av[2], ' ');
	if (!cmd1.args)
		exit(EXIT_FAILURE);
	if (close(fd[0]) == -1 || dup2(fd[1], 1) == -1 || close(fd[1])
		|| dup2(fd_inout[0], 0) == -1 || close(fd_inout[0]) == -1)
		exit (EXIT_FAILURE);
	cmd1.path = check_cmd_path(env, cmd1.args[0]);
	if (!cmd1.path)
		ft_error(cmd1.args[0]);
	execve(cmd1.path, cmd1.args, env);
}

void	ft_child2process(int *fd, int *fd_inout, char **av, char **env)
{
	t_idcmd	cmd2;

	cmd2.args = ft_split(av[3], ' ');
	if (!cmd2.args)
		exit(EXIT_FAILURE);
	if (close(fd[1]) == -1 || dup2(fd_inout[1], 1) == -1
		|| close(fd_inout[1]) == -1
		|| dup2(fd[0], 0) == -1 || close(fd[0]) == -1)
		exit (EXIT_FAILURE);
	cmd2.path = check_cmd_path(env, cmd2.args[0]);
	if (!cmd2.path)
		ft_error(cmd2.args[0]);
	execve(cmd2.path, cmd2.args, env);
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

void	ft_exitstatus(int status)
{
	int	exitstatus;

	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
		if (exitstatus)
			exit(exitstatus);
	}
}
