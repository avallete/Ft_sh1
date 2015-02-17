/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 18:22:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/17 12:41:36 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_unsetenv(t_env *env, char *key)
{
	int i;
	int e;
	int f;
	char **newenv;

	i = 0;
	e = 0;
	f = 0;
	if (env->infos->env)
	{
		if ((i = ft_findkey(env->infos->env, key)) > -1)
		{
			newenv = (char**)malloc(sizeof(char*) * SIZE_ENV - 1);
			while (e < SIZE_ENV)
			{
				if (e != i)
					newenv[f] = ft_strdup(C_ENV[e]), f++;
				e++;
			}
			newenv[f] = NULL;
			ft_splitdel(C_ENV);
			C_ENV = newenv;
			SIZE_ENV -= 1;
		}
	}
}
