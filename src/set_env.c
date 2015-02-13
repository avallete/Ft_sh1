/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 17:45:38 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 19:08:33 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_setenv(t_env *env, char *key, char *value)
{
	char *tmp;
	char *join;
	int	i;

	i = 0;
	join = ft_strjoin(key, "=");
	tmp = join;
	join = ft_strjoin(join, value);
	free(tmp);
	if (env->infos->env)
	{
		if (((i = ft_tabstrcmp(env->infos->env, key)) == -1))
			ft_recreatenv(env, join);
		else
		{
			tmp = env->infos->env[i];
			env->infos->env[i] = ft_strdup(join);
			free(tmp);
		}
	}
	if (join)
		free(join);
}

void	ft_recreatenv(t_env *env, char *str)
{
	char **tmp;

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
