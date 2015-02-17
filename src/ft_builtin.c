/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:31:25 by avallete          #+#    #+#             */
/*   Updated: 2015/02/17 09:58:24 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

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
		else
			ret = check_cd(env, list);
	}
	return (ret);
}
