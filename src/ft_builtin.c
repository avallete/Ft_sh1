/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:31:25 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 17:38:14 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char	check_setenv(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if ((!(ft_strcmp("setenv", *C_CARG(list)))))
	{
		if (ft_splitlen(C_CARG(list)) < 4)
		{
			if (C_CARG(list)[1] == NULL)
				ft_splitprint(C_ENV);
			else if (C_CARG(list)[1] && C_CARG(list)[2])
				ft_setenv(env, C_CARG(list)[1], C_CARG(list)[2]);
			else if (C_CARG(list)[1] && (!(C_CARG(list)[2])))
				ft_setenv(env, C_CARG(list)[1], "");
		}
		else
			ETOOMANYARG("setenv");
		ret = 1;
	}
	return (ret);
}

char	check_env(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if ((!(ft_strcmp("env", *C_CARG(list)))))
	{
		if (C_CARG(list)[1] == NULL)
			ft_splitprint(C_ENV), (ret = 1);
		else
			(C_CARG(list) = ft_resizesplit(C_CARG(list), 1, \
			   ft_splitlen(C_CARG(list))));
	}
	return (ret);
}

char	check_unsetenv(t_env *env, t_cmd *list)
{
	char ret;
	int	i;

	i = 1;
	ret = 0;
	if (!(ft_strcmp("unsetenv", *C_CARG(list))))
	{
		if (C_CARG(list)[1] == NULL)
			ETOOFEWARG("unsetenv");
		else
			while (C_CARG(list)[i])
				ft_unsetenv(env, C_CARG(list)[i++]);
			ret = 1;
	}
	return (ret);
}

char	check_exit(t_env *env, t_cmd *list)
{
	char	ret;
	int	e;

	ret = 0;
	e = 0;
	if (list)
	{
		if (!(ft_strcmp("exit", *C_CARG(list))))
		{
			if (C_CARG(list)[2])
			{
				ETOOMANYARG("exit");
			}
			else
			{
				C_CARG(list)[1] ? (e = ft_atoi(C_CARG(list)[1]))
				: (e = 0);
				free_them_all(env);
				exit(e);
				ret = 1;
			}
		}
	}
	return (ret);
}

char	check_builtin(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if (list)
	{
		if ((ret = check_exit(env, list)))
			return (ret);
		else if ((ret = (check_env(env, list))))
			return (ret);
		else if ((ret = (check_setenv(env, list))))
			return (ret);
		else if ((ret = (check_unsetenv(env, list))))
			return (ret);
	}
	return (ret);
}
