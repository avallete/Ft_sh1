/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:22:23 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:05:02 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** This function search why cd have failed
** and display a error message
*/

int		check_filerror(char *path)
{
	struct stat	lstat_s;
	struct stat	stat_s;

	if (((lstat(path, &lstat_s)) > -1))
	{
		if (S_ISDIR(lstat_s.st_mode) || S_ISLNK(lstat_s.st_mode))
		{
			if (S_ISLNK(lstat_s.st_mode) && (stat(path, &stat_s)) == -1)
				EBADLOOP(path);
			else if (lstat_s.st_mode & S_IRGRP)
				EBADDIR(path);
			else
				EBADACCESS(path);
		}
		else
			EBADDIR(path);
	}
	else
		EBADFILE(path);
	return (-1);
}

int		change_rep(t_env *env, char *path)
{
	int		ret;
	char		*e;
	char	pwd[MAXPATHLEN];
	char	npath[MAXPATHLEN];

	e = getcwd(pwd, PATH_MAX);
	ret = chdir(path);
	if (ret > -1)
	{
		if (e)
			ft_setenv(env, "OLDPWD", pwd);
		e = getcwd(npath, PATH_MAX);
		if (e)
			ft_setenv(env, "PWD", npath);
		return (0);
	}
	check_filerror(path);
	return (-1);
}
