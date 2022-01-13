/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 20:18:17 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/13 12:57:33 by dkramer       ########   odam.nl         */
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
	char	*hs;
	char	*hs2;
	char	*hs3;
	char	**args;
	int		fd;
}				t_pipex;

#endif