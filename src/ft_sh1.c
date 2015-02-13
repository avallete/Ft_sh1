/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:11:30 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 12:31:44 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		main(int ac, char **av, char **env)
{
	t_env	e;
	t_inf	inf;

	if (ac || av)
		ac = ac;
	e.cmd = NULL;
	inf.env = env;
	e.infos = &inf;
	while (1)
		print_inv(&e);
	return (0);
}
