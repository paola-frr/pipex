/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:20:40 by pferreir          #+#    #+#             */
/*   Updated: 2023/05/11 23:49:59 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*supstrjoin(char *s1, char *s2, char sep)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (ft_printf("malloc failed\n"), NULL);
	while (s1 && s1[j])
	{
		s[j] = s1[j];
		j++;
	}
	s[j++] = sep;
	while (s2 && s2[i])
	{
		s[i + j] = s2[i];
		i++;
	}
	s[i + j] = '\0';
	return (s);
}

void	right_args(t_pipex *data)
{
	int	i;

	i = 0;
	while(data->cmd_args[i])
	{
		if (data->cmd_args[i][0] == '-')
			data->cmd_args[i]++;
		i++;
	}
}

int	cmd_args_and_paths(t_pipex *data, char **argv, char **env, int i)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (!ft_strnstr(env[j], "PATH=", 5))
		j++;
	data->cmd_paths = ft_split(env[j] + 5, ':');
	if (!data->cmd_paths)
		return (ft_printf("no path found\n"), 1);
	ft_memset(data->cmd_args, 0, sizeof(data->cmd_args));
	while(data->cmd_args[k])
	{
		fprintf(stderr, "iteration %d : %s\n", k, data->cmd_args[k]);
		k++;
	}
	data->cmd_args = ft_split(argv[i], ' ');
	if (data->cmd_args == NULL)
		return (ft_printf("could not read the command\n"), 1);
	j = 0;
	while(data->cmd_paths[j])
	{
		data->cmd = supstrjoin(data->cmd_paths[j], data->cmd_args[0], '/');;
		if (access(data->cmd, F_OK | X_OK) != -1)
			return (1);
		j++;
		free(data->cmd);
	}
	ft_printf("command not found\n");
	return (0);
}
