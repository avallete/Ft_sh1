/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 18:08:26 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:00:59 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	rescue_env(t_env *env)
{
	int i;

	i = 0;
	if (C_ENV)
	{
		if ((i = ft_findkey(env->infos->env, "PATH")) == -1)
			found_pathrescue(env);
		if ((i = ft_findkey(env->infos->env, "PWD")) == -1)
			found_pwdrescue(env);
		if ((i = ft_findkey(env->infos->env, "HOME")) == -1)
			found_homerescue(env);
		if (((i = ft_findkey(env->infos->env, "USER")) == -1))
			found_usernamerescue(env);
	}
}
