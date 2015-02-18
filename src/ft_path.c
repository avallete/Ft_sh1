/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 14:49:11 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:05:15 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	init_path(t_env *env)
{
	char	*envpath;
	int		i;

	envpath = NULL;
	if (C_CPATH)
		ft_splitdel(C_CPATH);
	i = ft_findkey(C_ENV, "PATH");
	if (i > -1)
	{
		envpath = ft_strdup(C_ENV[i] + 5);
		C_CPATH = ft_strsplit(envpath, ':');
	}
	ft_secfree(envpath);
}
