/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 18:44:33 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

char	*find_commande(t_env *env, char *cmd)
{
	int i;
	char *tmp;
	char *good_path;

	tmp = NULL;
	i = 0;
	good_path = NULL;
	if (C_CPATH)
	{
		while (C_CPATH[i] && *C_CPATH[i])
		{
			good_path = ft_strjoin(C_CPATH[i], "/");
			tmp = ft_strjoin(good_path, cmd);
			if (tmp && access(tmp, X_OK) > -1)
			{
				ft_secfree(good_path);
				return (tmp);
			}
			else
				ft_secfree(tmp), ft_secfree(good_path);
			i++;
		}
	}
	return (NULL);
}

void	check_cmd(t_env *env, t_cmd *list)
{
	char *pathcmd;

	pathcmd = NULL;
	if ((pathcmd = find_commande(env, C_CARG(list)[0])))
	{
		env->infos->father = fork();
		if (!(check_toolongarg(C_CARG(list))))
		{
			if (env->infos->father > 0)
				wait(NULL);
			if (env->infos->father == 0)
				execve(pathcmd, C_CARG(list), C_ENV);
			ft_secfree(pathcmd);
		}
	}
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
			check_cmd(env, list);
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
	if (env->cmd)
		read_list(env, env->cmd);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
