/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 19:31:23 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/22 15:07:49 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>

void	parentprocess(int *pipefd, char **argv, char **newenv, t_pipex *pipex)
{
	if (close(pipefd[1]) == -1)
		exit(EXIT_FAILURE);
	// if (close(pipefd[0]) == -1)
	// {
	// 	// ft_putendl_fd("bye", 2);
	// 	exit(EXIT_FAILURE);
	// }
	if (access(argv[4], 0000) == 0)
		if (unlink(argv[4]) == -1)
			exit(EXIT_FAILURE);
	getpathoptions(argv, 3, pipex, newenv);
	// printf("%s\n", pipex->options);
	// exit (7);
	// if (pipex->extraoptions)
	// {
	// 	free (pipex->split[2]);
	// 	exit (EXIT_FAILURE);
	// }
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->ls;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	// pipex->fd = open(argv[1], O_RDONLY);
	// if (pipex->fd == -1)
	// 	exit(EXIT_FAILURE);
	pipex->fd = open(argv[4], O_RDWR | O_CREAT, 0444);
	// printf("%d\n", pipex->fd);
	// exit (7);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	// if (dup2(pipex->fd, 0) == -1)
	// 	exit(EXIT_FAILURE);
	// if (dup2(pipefd[1], 1) == -1)
	// 	exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 1) == -1 || dup2(pipefd[0], 0) == -1)
		exit(EXIT_FAILURE);
	ft_execute(pipex, newenv, argv[3]);
	
}

void	childprocess(int *pipefd, char **argv, char **newenv, t_pipex *pipex)
{
	// int status;

	// if (close(pipefd[1]) == -1)
	// 	exit(EXIT_FAILURE);
	if (close(pipefd[0]) == -1)
	{
		// ft_putendl_fd("bye", 2);
		exit(EXIT_FAILURE);
	}
	getpathoptions(argv, 2, pipex, newenv);
	// if (pipex->extraoptions)
	// {
	// 	free (pipex->split[2]);
	// 	exit (2);
	// }
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->ls;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	pipex->fd = open(argv[1], O_RDONLY);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	// if (dup2(pipex->fd, 1) == -1)
	// 	exit(EXIT_FAILURE);
	// if (dup2(pipefd[0], 0) == -1)
	// 	exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 0) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], 1) == -1)
		exit(EXIT_FAILURE);
	ft_execute(pipex, newenv, argv[2]);
	// exit (127);
	// waitpid(pipex->cpid, &status, 0);
	// if (WIFEXITED(status))
	// 	exit(status);
}

int	main(int argc, char *argv[], char **newenv)
{
	int		pipefd[2];
	t_pipex	pipex;
	pid_t	cpid;

	// pipex.cmd = 0;
	if (argc != 5)
		exit(EXIT_FAILURE);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		// int status;
	
		// waitpid(cpid, &status, 0);
		// if (WIFEXITED(status))
		// 	exit(7);
		childprocess(pipefd, argv, newenv, &pipex);
		// ft_execute(&pipex, newenv);
	}
	else
	{
		// int status;
	
		// waitpid(cpid, &status, 0);
		// if (WIFEXITED(status))
			// exit(7);
		// int status;
	
		waitpid(pipefd[1], NULL, 0);
		parentprocess(pipefd, argv, newenv, &pipex);
		// ft_execute(&pipex, newenv);
	}
}
