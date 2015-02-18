/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:25:56 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:06:19 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contain some functions for access env key/value.
*/

#include <ft_sh.h>

char	*key_value(char *env)
{
	int i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	i++;
	if (env[i])
		return (ft_strdup(env + i));
	else
		return (ft_strdup(""));
}

int		ft_findkey(char **tab, char *str)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], str) == '=')
			return (i);
		i++;
	}
	return (-1);
}
