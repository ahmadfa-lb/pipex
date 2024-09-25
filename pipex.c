/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:48:01 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/13 10:49:59 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	forkinit(char **argv, char **envp, t_pf pipe_x, t_cmd cmd_x)
{
	pipe_x.pid1 = fork();
	if (pipe_x.pid1 == 0)
		work_child1(argv, envp, pipe_x, cmd_x);
	else
		perror("ERROR IN fork1");
	pipe_x.pid2 = fork();
	if (pipe_x.pid2 == 0)
		work_child2(argv, envp, pipe_x, cmd_x);
	else
		perror("ERROR IN fork2");
}

int	main(int argc, char **argv, char **envp)
{
	t_pf	pipe_x;
	t_cmd	cmd_x;

	if (argc != 5)
		handle_error("Usage: ./pipex file1 cmd1 cmd2 file2");
	pipe_x.in_fd = open(argv[1], O_RDONLY);
	if (pipe_x.in_fd == -1)
		handle_error("INFILE NOT FOUND !!");
	pipe_x.out_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipe_x.out_fd == -1)
		handle_error("ERROR IN  OPENING OUTFILE !!");
	if (pipe(pipe_x.pipefd) == -1)
		handle_error("ERROR IN PIPE !!");
	cmd_x.paths = find_path(envp);
	cmd_x.cmd_paths = ft_split(cmd_x.paths, ':');
	forkinit(argv, envp, pipe_x, cmd_x);
	close(pipe_x.pipefd[0]);
	close(pipe_x.pipefd[1]);
	wait(NULL);
	wait(NULL);
	free_after_parent_work(&pipe_x, &cmd_x);
	return (0);
}
