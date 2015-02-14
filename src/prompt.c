/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 12:44:10 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	ft_perror(int err)
{
}

char	check_setenv(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if ((!(ft_strcmp("setenv", *C_CARG(list)))))
	{
		if (C_CARG(list)[1] == NULL)
			ft_splitprint(C_ENV), ret = 1;
		else if (C_CARG(list)[1] && C_CARG(list)[2])
			ft_setenv(env, C_CARG(list)[1], C_CARG(list)[2]), ret = 1;
		else if (C_CARG(list)[1] && (!(C_CARG(list)[2])))
			ft_setenv(env, C_CARG(list)[1], ""), ret = 1;
		else
			ret = 0;
	}
	ft_splitprint(C_ENV);
	return (ret);
}

char	check_env(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if ((!(ft_strcmp("env", *C_CARG(list)))))
	{
		if (C_CARG(list)[1] == NULL)
			ft_splitprint(C_ENV), (ret = 1);
		else
			(C_CARG(list) = ft_resizesplit(C_CARG(list), 1, \
			ft_splitlen(C_CARG(list))));
	}
	return (ret);
}

char	check_buitin(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if (list)
	{
		if ((ret = (check_setenv(env, list))))
			return (ret);
		if ((ret = (check_env(env, list))))
			return (ret);
	}
	return (ret);
}

void	read_list(t_env *env, t_cmd *list)
{
	if (list)
	{
		if (!(check_buitin(env, list)))
		{
			env->infos->father = fork();
			if (env->infos->father > 0)
				execve("/bin/echo", C_CARG(list), C_ENV);
		}
		if (list->next && env->infos->father == 0)
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
	ft_putstr("$> ");
	ft_init_cmd(env);
	read_list(env, env->cmd);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
