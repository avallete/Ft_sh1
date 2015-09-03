/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 12:55:18 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 12:57:26 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		check_correctcmd(char *path)
{
	if (path)
	{
		if ((access(path, F_OK)) >= 0)
		{
			if (access(path, X_OK) >= 0 && access(path, R_OK) >= 0)
				return (1);
		}
	}
	return (0);
}

char	*find_commande(t_env *env, char *cmd)
{
	int		i;
	char	*tmp;
	char	*good_path;

	i = 0;
	if (C_CPATH)
	{
		if (check_correctcmd(cmd))
			return (ft_strdup(cmd));
		while (C_CPATH[i] && *C_CPATH[i])
		{
			good_path = ft_strjoin(C_CPATH[i], "/");
			tmp = ft_strjoin(good_path, cmd);
			if (tmp && check_correctcmd(tmp))
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

	if (list && C_CARG(list) && *C_CARG(list))
	{
		if ((pathcmd = find_commande(env, C_CARG(list)[0])))
		{
			if (!(check_toolongarg(C_CARG(list))))
			{
				env->infos->father = fork();
				if (env->infos->father > 0)
					waitpid(env->infos->father, NULL, 0);
				if (env->infos->father == 0)
					execve(pathcmd, C_CARG(list), C_ENV);
				ft_secfree(pathcmd);
			}
		}
		else
			EINVALCMD(C_CARG(list)[0]);
	}
}

void	read_list(t_env *env, t_cmd *list)
{
	char ret;

	ret = 1;
	rescue_env(env);
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
