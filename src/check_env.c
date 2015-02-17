/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:30:09 by avallete          #+#    #+#             */
/*   Updated: 2015/02/17 12:45:17 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** This file find if cmd is a builtin type env
 ** he exectute them if cmd have valid argument and return error else
 */

#include <ft_sh.h>

char	check_env(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if (list && C_CARG(list) && *C_CARG(list))
	{
		if ((!(ft_strcmp("env", *C_CARG(list)))))
		{
			if (C_CARG(list)[1] == NULL)
				ft_splitprint(C_ENV), (ret = 1);
			else
				(C_CARG(list) = ft_resizesplit(C_CARG(list), 1, \
											   ft_splitlen(C_CARG(list))));
		}
	}
	return (ret);
}

char	check_unsetenv(t_env *env, t_cmd *list)
{
	char ret;
	int	i;

	i = 1;
	ret = 0;
	if (list && C_CARG(list) && *C_CARG(list))
	{
		if (!(ft_strcmp("unsetenv", *C_CARG(list))))
		{
			if (C_CARG(list)[1] == NULL)
				ETOOFEWARG("unsetenv");
				while (C_CARG(list)[i])
				{
					if (!(ft_strchr(C_CARG(list)[i], '=')))
						ft_unsetenv(env, C_CARG(list)[i]);
					i++;
				}
			ret = 1;
		}
	}
	return (ret);
}
