/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:11:30 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 19:08:35 by avallete         ###   ########.fr       */
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
	inf.size_env = ft_splitlen(env);
	inf.env = copy_env(env, inf.size_env);
	inf.father = 0;
	e.infos = &inf;
	ft_printf("BEFORE : \n");
	ft_splitprint(inf.env);
	ft_setenv(&e, "TEST", "kikoulol");
	ft_setenv(&e, "TEST", "kikool");
	ft_unsetenv(&e, "PATH");
	ft_printf("After : \n");
	ft_splitprint(inf.env);
	while (1)
		print_inv(&e);
	if (inf.paths)
		ft_splitdel(inf.paths);
	return (0);
}
