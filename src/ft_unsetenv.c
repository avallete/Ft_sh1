/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 18:22:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 17:51:27 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_unsetenv(t_env *env, char *key)
{
	int i;

	i = 0;
	if (env->infos->env)
	{
		if ((i = ft_tabstrcmp(env->infos->env, key)) > -1)
		{
			free(env->infos->env[i]);
			env->infos->env[i] = ft_strdup(env->infos->env[SIZE_ENV - 1]);
			free(env->infos->env[SIZE_ENV - 1]);
			env->infos->env[SIZE_ENV - 1] = NULL;
			SIZE_ENV -= 1;
		}
	}
}
