/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:11:30 by avallete          #+#    #+#             */
/*   Updated: 2015/02/12 19:27:44 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		main(void)
{
	t_env	env;

	env.cmd = NULL;
	env.infos = NULL;
	free_split((ft_strsplit("woifj oiwjf oiwjfoi owifj ", ' ')));
	free_split((ft_strsplit("woifj oiwjf oiwjfoi owifj ", ' ')));
	free_split((ft_strsplit("woifj oiwjf oiwjfoi owifj ", ' ')));
	free_split((ft_strsplit("woifj oiwjf oiwjfoi owifj ", ' ')));
	while (1)
	{
	}
	//	print_inv(&env);
	return (0);
}
