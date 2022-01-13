/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 19:31:23 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/13 13:54:56 by dkramer       ########   odam.nl         */
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

void	getpathandoptions(char **argv, int argint, t_pipex *pipex)
{
	pipex->split = ft_split(argv[argint], ' ');
	if (!pipex->split)
		exit(EXIT_FAILURE);
	pipex->ls = ft_strdup(pipex->split[0]);
	if (!pipex->ls)
		exit(EXIT_FAILURE);
	pipex->options = NULL;
	if (pipex->split[1])
	{
		pipex->options = ft_strdup(pipex->split[1]);
		if (!pipex->options)
			exit(EXIT_FAILURE);
	}
	if (!ft_strnstr(pipex->hs, pipex->ls, ft_strlen(pipex->hs))
		&& !ft_strnstr(pipex->hs2, pipex->ls, ft_strlen(pipex->hs2))
		&& !ft_strnstr(pipex->hs3, pipex->ls, ft_strlen(pipex->hs3)))
		pipex->path = ft_strjoin("/usr/bin/", pipex->ls);
	else
		pipex->path = ft_strjoin("/bin/", pipex->ls);
	if (pipex->path == 0)
		exit(EXIT_FAILURE);
	free (pipex->split[0]);
	free (pipex->split[1]);
	free (pipex->split);
}

void	parentprocess(int *pipefd, char **argv, char **newenv, t_pipex *pipex)
{
	if (close(pipefd[0]) == -1)
		exit(EXIT_FAILURE);
	if (access(argv[4], 0444) == 0)
		if (unlink(argv[4]) == -1)
			exit(EXIT_FAILURE);
	getpathandoptions(argv, 2, pipex);
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->path;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	pipex->fd = open(argv[1], O_RDONLY);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 0) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], 1) == -1)
		exit(EXIT_FAILURE);
	if (execve(pipex->args[0], pipex->args, newenv) == -1)
		exit(EXIT_FAILURE);
}

void	childprocess(int *pipefd, char **argv, char **newenv, t_pipex *pipex)
{
	if (close(pipefd[1]) == -1)
		exit(EXIT_FAILURE);
	getpathandoptions(argv, 3, pipex);
	pipex->args = malloc(sizeof(char *) * 4);
	if (!pipex->args)
		exit(EXIT_FAILURE);
	pipex->args[0] = pipex->path;
	if (pipex->options)
		pipex->args[1] = pipex->options;
	pipex->fd = open(argv[4], O_RDWR | O_CREAT, 0444);
	if (pipex->fd == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipex->fd, 1) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[0], 0) == -1)
		exit(EXIT_FAILURE);
	if (execve(pipex->args[0], pipex->args, newenv) == -1)
		exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char **newenv)
{
	int		pipefd[2];
	pid_t	cpid;
	t_pipex	pipex;

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
	pipex.hs = "[ df ln sh bash echo ls sleep cat ed mkdir stty chmod";
	pipex.hs2 = "expr mv sync cp hostname pax tcsh csh kill ps test dash";
	pipex.hs3 = "ksh pwd unlink date launchctl rm wait4path dd link rmdir zsh";
	if (cpid == 0)
		childprocess(pipefd, argv, newenv, &pipex);
	else
		parentprocess(pipefd, argv, newenv, &pipex);
}
