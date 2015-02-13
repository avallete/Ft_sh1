/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstrcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 17:13:55 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 17:22:48 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_tabstrcmp(char **tab, char *str)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
