/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:11:30 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 12:36:37 by avallete         ###   ########.fr       */
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
	inf.father = 0;
	inf.paths = NULL;
	inf.size_env = ft_splitlen(env);
	inf.env = copy_env(env, inf.size_env);
	e.infos = &inf;
	while (1)
		print_inv(&e);
	free_them_all(&e);
	return (0);
}
