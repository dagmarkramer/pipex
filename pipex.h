/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 20:18:17 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/24 15:12:24 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	char	**split;
	char	*ls;
	char	*options;
	char	*path;
	char	**path2d;
	char	*hs;
	char	*hs2;
	char	*hs3;
	char	**args;
	int		fd;
	char 	*extraoptions;

	// int		cmd;
	pid_t	cpid;
}				t_pipex;

void	ft_execute(char **path2d, char *ls, char **args, char **newenv);
void	getpathoptions(char **argv, int argint, t_pipex *pipex, char **newenv);

#endif