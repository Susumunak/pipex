/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:31:23 by del-khay          #+#    #+#             */
/*   Updated: 2022/11/22 01:13:11 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/pipex_bonus.h"

void	ft_free2(char **string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	unsigned int	size;
	unsigned int	i;
	char			*rslt;

	if (!s1 || !s2)
		return (0);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	rslt = (char *) malloc(sizeof(char) * size);
	if (!rslt)
		return (0);
	while (*s1)
		rslt[i++] = *s1++;
	while (*s2)
		rslt[i++] = *s2++;
	rslt[i] = 0;
	return (rslt);
}

char	*ft_strjoin(char *dst, char *src)
{
	char	*rst;
	int		i;

	i = 0;
	if (!dst)
	{
		dst = ft_calloc(1, sizeof(char));
		if (!dst)
			return (0);
	}
	rst = ft_calloc(ft_strlen(dst) + ft_strlen(src) + 1, sizeof(char));
	if (!rst)
		return (0);
	while (dst && dst[i])
	{
		rst[i] = dst[i];
		i++;
	}
	while (*src)
		rst[i++] = *src++;
	free(dst);
	return (rst);
}

char	*ft_getenv(char **env)
{
	char	*path_env;

	path_env = 0;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", ft_strlen(*env)))
		{
			path_env = ft_strnstr(*env, "PATH=", ft_strlen(*env)) + 5;
			return (path_env);
		}
		env++;
	}
	return (0);
}

char	*check_cmd_path(char **env, char *cmd)
{
	char	*path;
	char	**paths;
	char	*cmd_prefix;
	int		i;

	i = 0;
	if (!access(cmd, F_OK || X_OK))
		return (cmd);
	cmd_prefix = ft_strjoin(ft_strdup("/"), cmd);
	path = ft_getenv(env);
	paths = ft_split(path, ':');
	while (paths && paths[i])
	{
		path = ft_strjoin2(paths[i], cmd_prefix);
		if (!access(path, F_OK || X_OK))
		{
			free(cmd_prefix);
			ft_free2(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd_prefix);
	return (0);
}
