/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:23:32 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:09:07 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** All misc functions usefull for CD builtin
*/

char	*make_good_path(char *path)
{
	size_t	end;
	char	*tmp;

	end = ft_strlen(path);
	if (path[end - 1] != '/')
	{
		tmp = path;
		path = ft_strjoin(path, "/");
		free(tmp);
	}
	return (path);
}

void	go_oldpwd(t_env *env)
{
	int		oldpwd;
	char	*oldpwdval;

	oldpwd = -1;
	oldpwdval = NULL;
	oldpwd = ft_findkey(C_ENV, "OLDPWD");
	if (oldpwd > -1)
		oldpwdval = key_value(C_ENV[oldpwd]);
	if (oldpwdval && *oldpwdval)
		change_rep(env, oldpwdval), free(oldpwdval), oldpwdval = NULL;
}

void	go_home(t_env *env)
{
	int		home;
	char	*homeval;

	homeval = NULL;
	home = -1;
	home = ft_findkey(C_ENV, "HOME");
	if (home > -1)
		homeval = key_value(C_ENV[home]);
	if (homeval)
		change_rep(env, homeval), free(homeval), homeval = NULL;
}

void	go_tild(char *tild, t_env *env)
{
	int		home;
	char	*homeval;
	char	*joinpath;

	homeval = NULL;
	home = -1;
	home = ft_findkey(C_ENV, "HOME");
	if (home > -1)
		homeval = key_value(C_ENV[home]);
	if (homeval)
	{
		joinpath = ft_strjoin(homeval, tild + 1);
		change_rep(env, joinpath);
		free(joinpath);
		free(homeval);
	}
}
