/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:07:31 by pferreir          #+#    #+#             */
/*   Updated: 2023/05/09 23:30:49 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirection_input_output(t_pipex *data)
{
	int	fd;

	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
	{
		perror(data->infile);
		// ft_printf("no such file or directory: %s\n", data->infile);
		return (0);
	}
	// if (access(data->cmd, R_OK) != -1)
		// ft_printf("permission denied: %s\n", data->infile);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return(1);
}

int	redirection(t_pipex *data, int i)
{
	int	fd;

	if (i == 0 && !redirection_input_output(data))
		return (0);
	if (i == data->nbcmd - 1)
	{
		fd = open(data->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (fd == -1)
			return(ft_printf("permission denied : %s\n", data->outfile), 0);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	if (i != 0)
	{
		dup2(data->prev, STDIN_FILENO);
		close(data->prev);
	}
	if (i != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	return (1);
}

int	wait_kids(t_pipex *data)
{
	int	i;

	i = 0; 
	close(data->fd[0]);

	while(i < data->nbcmd)
	{
		waitpid(data->pid[i++], 0, 0);
		i++;
	}
	free(data->pid);
	return(1);
}

int	exec_commands(t_pipex *data, char **argv, char **env)
{
	int	i;

	i = -1;
	while (++i < data->nbcmd)
	{
		pipe(data->fd);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			ft_printf("fork failed\n");
			exit(EXIT_FAILURE);
		}
		else if (!data->pid[i])
		{
			if (!redirection(data, i) || !cmd_args_and_paths(data, argv, env, i + 2))
				return (exit(EXIT_FAILURE), 0);
			fprintf(stderr, "{%s}\n", argv[i + 2]);
			execve(data->cmd, data->cmd_args, env);
			exit (EXIT_FAILURE);
		}
		else if (data->pid[i] > 0)
		{
			close(data->fd[1]);
			if (data->prev != -1)
				close(data->prev);
			data->prev = data->fd[0];
		}
	}
	return (wait_kids(data));
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;

	if (argc < 5)
		return (ft_printf("parse error near `|'\n"), 0);
	ft_memset(&data, 0, sizeof(data));
	data.nbcmd = argc - 3;
	data.prev = -1;
	data.pid = malloc(sizeof(int) * data.nbcmd);
	if (!data.pid)
		return (ft_printf("malloc failed\n"), 0);
	data.infile = argv[1];
	data.outfile = argv[argc - 1];
	exec_commands(&data, argv, env);
	return (0);
}
