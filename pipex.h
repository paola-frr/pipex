/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferreir <pferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:07:19 by pferreir          #+#    #+#             */
/*   Updated: 2023/05/09 20:57:08 by pferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>
# include <signal.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_pipex
{
	pid_t	*pid;
	int		success;
	int		fd[2];
	int		prev;
	int		nbcmd;
	char	*infile; 
	char	*outfile; 
	char	*paths; 
	char	**cmd_paths;
	char	**cmd_args; 
	char	*cmd; 
}			t_pipex;


int		redirection_input_output(t_pipex *data);
int		redirection(t_pipex *data, int i);
void	right_args(t_pipex *data);
void	wait_kid(t_pipex *data);
int		cmd_args_and_paths(t_pipex *data, char **argv, char **env, int i);
int		cmd_args(t_pipex *data, char **argv, int i);
char	*supstrjoin(char *s1, char *s2, char sep);
int		exec_commands(t_pipex *data, char **argv, char **env);

#endif