/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:30:56 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 16:09:43 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	int	fd_io[2];

	if (ac < 5)
	{
		ft_putendl_fd("Number of args is incorrect", 2);
		return (1);
	}
	fd_io[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_io[1] == -1)
	{
		perror(av[4]);
		return (errno);
	}
	fd_io[0] = open(av[1], O_RDONLY);
	if (fd_io[0] == -1)
		perror(av[1]);
	pipex(fd_io, av, env, ac -1);
}
