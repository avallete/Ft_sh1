/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 11:11:19 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	read_list(t_env *env, t_cmd *list)
{
	char ret;

	ret = 1;
	init_path(env);
	if (list)
	{
		ret = check_builtin(env, list);
		if (ret < 1)
		{
			env->infos->father = fork();
			if (!(check_toolongarg(C_CARG(list))))
			{
				if (env->infos->father > 0)
					execve("/bin/echo", C_CARG(list), C_ENV);
			}
		}
		if (list->next)
			read_list(env, list->next);
	}
}

void	ft_init_cmd(t_env *env)
{
	char	*buf;
	char	**svpoint;
	int		i;

	i = 0;
	svpoint = NULL;
	buf = NULL;
	while (!(get_next_line(0, &buf)))
		get_next_line(0, &buf);
	clear_cmd(buf);
	svpoint = ft_strsplit(buf, ';');
	while (svpoint[i])
		ft_wait_cmd(env, &svpoint[i]), i++;
	if (svpoint)
		ft_splitdel(svpoint);
	if (buf)
		free(buf);
	buf = NULL;
}

void	print_inv(t_env *env)
{
	rescue_env(env);
	ft_putstr("$> ");
	ft_init_cmd(env);
	read_list(env, env->cmd);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
