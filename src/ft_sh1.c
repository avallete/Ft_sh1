/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:11:30 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 17:42:05 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

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

int		main(int ac, char **av, char **env)
{
	t_env	e;
	t_inf	inf;

	if (ac || av)
		ac = ac;
	e.cmd = NULL;
	inf.size_env = ft_splitlen(env);
	inf.env = copy_env(env, inf.size_env);
	inf.father = 0;
	e.infos = &inf;
	ft_printf("BEFORE : \n");
	ft_splitprint(inf.env);
	ft_setenv(&e, "Un jolie", "test");
	ft_setenv(&e, "Un jolie", "test");
	ft_setenv(&e, "Un jolie", "test");
	ft_printf("After : \n");
	ft_splitprint(inf.env);
	while (1)
		print_inv(&e);
	if (inf.paths)
		ft_splitdel(inf.paths);
	return (0);
}
