/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:33:21 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 13:57:59 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** This function check if "cd" builtin is called
** if it is she exectuce cd with argument passed
** and return 1, else she return 0
*/

char	check_cd(t_env *env, t_cmd *list)
{
	char	ret;

	ret = 0;
	if (list)
	{
		if (!(ft_strcmp("cd", *C_CARG(list))))
		{
			if (C_CARG(list)[1])
			{
				if ((!(ft_strcmp(C_CARG(list)[1], "-"))))
					go_oldpwd(env);
				else if (C_CARG(list)[1][0] == '~')
					go_tild(C_CARG(list)[1], env);
				else if (C_CARG(list)[1][0] != '/')
					change_relrep(env, C_CARG(list)[1]);
				else
					change_absrep(env, C_CARG(list)[1]);
			}
			else
				go_home(env);
			ret = 1;
		}
	}
	return (ret);
}
