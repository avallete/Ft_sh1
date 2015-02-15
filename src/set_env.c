/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 17:45:38 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 18:51:56 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_setenv(t_env *env, char *key, char *value)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	join = format_envval(key, value);
	if (env->infos->env && join)
	{
		if (((i = ft_findkey(env->infos->env, key)) == -1))
			ft_recreatenv(env, join);
		else
		{
			if (env->infos->env[i])
				tmp = env->infos->env[i];
			env->infos->env[i] = ft_strdup(join);
			if (tmp)
				free(tmp);
		}
	}
	if (join)
		free(join);
}

void	ft_recreatenv(t_env *env, char *str)
{
	char **tmp;

	tmp = NULL;
	if (env->infos->env)
		tmp = env->infos->env;
	if (env->infos->env && str && *str)
	{
		env->infos->env = copy_env(env->infos->env, env->infos->size_env + 1);
		env->infos->env[SIZE_ENV] = ft_strdup(str);
		env->infos->env[SIZE_ENV + 1] = NULL;
		SIZE_ENV += 1;
		if (tmp)
			ft_splitdel(tmp);
	}
}

char	**copy_env(char **env, size_t size)
{
	char **ecop;
	int i;

	i = 0;
	if (env)
	{
		ecop = (char**)malloc(sizeof(char*) * size + 1);
		while (env[i])
			ecop[i] = ft_strdup(env[i]), i++;
		ecop[size] = NULL;
	}
	return (ecop);
}
