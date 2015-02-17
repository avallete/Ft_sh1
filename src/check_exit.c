/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:32:38 by avallete          #+#    #+#             */
/*   Updated: 2015/02/17 09:55:01 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char	check_exit(t_env *env, t_cmd *list)
{
	char	ret;
	int	e;

	ret = 0;
	e = 0;
	if (list && C_CARG(list) && *C_CARG(list))
	{
		if (!(ft_strcmp("exit", *C_CARG(list))))
		{
			if (ft_splitlen(C_CARG(list)) > 2)
				ETOOMANYARG("exit");
			else
			{
				C_CARG(list)[1] ? (e = ft_atoi(C_CARG(list)[1]))
					: (e = 0);
				free_them_all(env);
				exit(e);
			}
			ret = 1;
		}
	}
	return (ret);
}


