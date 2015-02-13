/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 17:26:23 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 17:28:32 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_splitprint(char **split)
{	
	int i;

	i = 0;
	if (split)
	{
		while (split[i])
			ft_putendl(split[i]), i++;
	}
}
