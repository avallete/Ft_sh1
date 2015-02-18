/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 12:44:13 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf[0])
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	ft_init_cmd(t_env *env)
{
	char	*buf;
	char	**svpoint;
	int		i;

	i = 0;
	svpoint = NULL;
	buf = NULL;
	if (get_next_line(0, &buf))
	{
		clear_cmd(buf);
		svpoint = ft_strsplit(buf, ';');
		while (svpoint[i])
			ft_wait_cmd(env, &svpoint[i]), i++;
		if (svpoint)
			ft_splitdel(svpoint);
		if (buf)
			free(buf);
	}
	else
		free_them_all(env), exit(0);
}

void	print_prompt(int sig)
{
	if (sig)
		ft_putstr("\n$> ");
}

void	print_inv(t_env *env)
{
	rescue_env(env);
	signal(SIGINT, print_prompt);
	ft_putstr("$> ");
	ft_init_cmd(env);
	if (env->cmd)
		read_list(env, env->cmd);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
