/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 19:31:23 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/24 16:22:29 by dkramer       ########   odam.nl         */
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
	if (close(pipefd[0]) == -1)
		exit(EXIT_FAILURE);
	if (access(argv[4], 0000) == 0)
		if (unlink(argv[4]) == -1)
			exit(EXIT_FAILURE);
	getpathoptions(argv, 2, pipex, newenv);
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->ls;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	// if (pipex->extraoptions)
	// {
	// 	pipex->args[2] = pipex->extraoptions;
	// 	free (pipex->split[2]);
	// 	exit (EXIT_FAILURE);
	// }
	pipex->fd = open(argv[1], O_RDONLY);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 0) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], 1) == -1)
		exit(EXIT_FAILURE);
	char	**path2d1 = pipex->path2d;
	char	*ls1 = pipex->ls;
	char	**args10 = pipex->args;
	ft_execute(path2d1, ls1, args10, newenv);
	exit (127);
// 	if (close(pipefd[0]) == -1)
// 		exit(EXIT_FAILURE);
// 	if (access(argv[4], 0000) == 0)
// 		if (unlink(argv[4]) == -1)
// 			exit(EXIT_FAILURE);
// 	getpathoptions(argv, 2, pipex, newenv);
// 	pipex->args = malloc(sizeof(char *) * 4);
// 	if (!pipex->args)
// 		exit(EXIT_FAILURE);
// 	pipex->args[0] = pipex->ls;
// 	if (pipex->options)
// 		pipex->args[1] = pipex->options;
// 	pipex->fd = open(argv[1], O_RDONLY);
// 	if (pipex->fd == -1)
// 		exit(EXIT_FAILURE);
// 	if (dup2(pipex->fd, 0) == -1)
// 		exit(EXIT_FAILURE);
// 	if (dup2(pipefd[1], 1) == -1)
// 		exit(EXIT_FAILURE);
	
// 	ft_execute(pipex, newenv);
// 	// int	status;
// 	// waitpid(pipex->cpid, &status, 0);
// 	// if (WIFEXITED(status))
// 	// 	exit(status);
// 	// exit(127);
}

void	childprocess(int *pipefd, char **argv, char **newenv, t_pipex *pipex)
{
	// if (close(pipefd[0]) == -1)
	// 	exit(EXIT_FAILURE);
	// if (access(argv[4], 0000) == 0)
	// 	if (unlink(argv[4]) == -1)
	// 		exit(EXIT_FAILURE);
	// getpathoptions(argv, 2, pipex, newenv);
	// pipex->args = malloc(sizeof(char *) * 4);
	// if (!pipex->args)
	// 	exit(EXIT_FAILURE);
	// pipex->args[0] = pipex->ls;
	// if (pipex->options)
	// 	pipex->args[1] = pipex->options;
	// pipex->fd = open(argv[1], O_RDONLY);
	// if (pipex->fd == -1)
	// 	exit(EXIT_FAILURE);
	// if (dup2(pipex->fd, 0) == -1)
	// 	exit(EXIT_FAILURE);
	// if (dup2(pipefd[1], 1) == -1)
	// 	exit(EXIT_FAILURE);
	// char	**path2d1 = pipex->path2d;
	// char	*ls1 = pipex->ls;
	// char	**args10 = pipex->args;
	// ft_execute(pipex, newenv);
	if (close(pipefd[1]) == -1)
		exit(EXIT_FAILURE);
	getpathoptions(argv, 3, pipex, newenv);
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->ls;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	// if (pipex->extraoptions)
	// {
	// 	pipex->args[2] = pipex->extraoptions;
	// 	free (pipex->split[2]);
	// 	exit (2);
	// }
	pipex->fd = open(argv[4], O_RDWR | O_CREAT, 0444);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 1) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[0], 0) == -1)
		exit(EXIT_FAILURE);
	// int	status;
	// waitpid(pipex->cpid, &status, 0);
	// if (WIFEXITED(status))
	// 	exit(status);
	char	**path2d2 = pipex->path2d;
	char	*ls2 = pipex->ls;
	char	**args20 = pipex->args;
	ft_execute(path2d2, ls2, args20, newenv);
	
	// exit (127);

	// ft_execute(path2d1, ls1, args10, newenv);

	

	// ft_execute(pipex, newenv);
	// exit(127);
	

}

int	main(int argc, char *argv[], char **newenv)
{
	int		pipefd[2];
	t_pipex	pipex;
	int		ended_process;
	int		errno;
	// int		status;

	errno = 0;
	ended_process = 0;
	// pipex.cmd = 0;
	if (argc != 5)
		exit(EXIT_FAILURE);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipex.cpid = fork();
	if (pipex.cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipex.cpid == 0)
		childprocess(pipefd, argv, newenv, &pipex);
	else
	{
		// while (ended_process != 0)
		// 	ended_process = waitpid(0, &status, 0);
		// if (((status) & 0x7f) == 0)
		// 	errno = ((status) & 0xff00) >> 8;
		parentprocess(pipefd, argv, newenv, &pipex);
		// exit (errno);
	}
	
}
