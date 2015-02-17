/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 10:04:44 by avallete          #+#    #+#             */
/*   Updated: 2015/02/17 12:22:13 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_choosesetenv(t_env *env, t_cmd *list)
{
	if (C_CARG(list)[1] == NULL)
		ft_splitprint(C_ENV);
	else if (!(ft_strchr(C_CARG(list)[1], '=')))
	{
		if (C_CARG(list)[1] && (!(C_CARG(list)[2])))
			ft_setenv(env, C_CARG(list)[1], "");
		else if (C_CARG(list)[1] && C_CARG(list)[2])
			ft_setenv(env, C_CARG(list)[1], C_CARG(list)[2]);
	}
	else
		ESETENVEG("setenv");
}

char	check_setenv(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if (list && C_CARG(list) && *C_CARG(list))
	{
		if ((!(ft_strcmp("setenv", *C_CARG(list)))))
		{
			if (ft_splitlen(C_CARG(list)) < 4)
				ft_choosesetenv(env, list);
			else
				ETOOMANYARG("setenv");
			ret = 1;
		}
	}
	return (ret);
}
