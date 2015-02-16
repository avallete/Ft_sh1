/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:22:23 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 17:10:45 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** This function search why cd have failed
** and display a error message
*/

int		check_filerror(char *path, char *arg)
{
	struct	stat	lstat_s;
	struct	stat	stat_s;

	if (((lstat(path, &lstat_s)) > -1))
	{
		if (S_ISDIR(lstat_s.st_mode) || S_ISLNK(lstat_s.st_mode))
		{
			if (S_ISLNK(lstat_s.st_mode) && (stat(path, &stat_s)) == -1)
				EBADLOOP(arg);
			else if (lstat_s.st_mode & S_IRGRP)
				EBADDIR(arg);
			else
				EBADACCESS(arg);
		}
		else
			EBADDIR(arg);
	}
	else
		EBADFILE(arg);
	return (-1);
}

/*
**This function grep a absolute pathname, check if it's OK
**Go them and edit PWD and OLDPWD value in env if OK
**Else she prompt a error and return a error.
*/

int	change_absrep(t_env *env, char *path)
{
	int ret;
	int pret;
	char *pwd;

	ret = -1;
	pret = ft_findkey(C_ENV, "PWD");
	if (pret > -1)
		pwd = key_value(C_ENV[pret]);
	if (path)
		ret = chdir(path);
	if (ret > -1)
	{
		if (ft_strcmp(pwd, path))
			ft_setenv(env, "OLDPWD", pwd);
		ft_setenv(env, "PWD", path);
		free(pwd);
		return (0);
	}
	check_filerror(pwd, path);
	ft_secfree(pwd);
	return (-1);
}

/*
** Same working of the change_absrep function but she use the relative path
** With using PWD env path and join them with 'path'
*/

int	change_relrep(t_env *env, char *path)
{
	int ret;
	int pret;
	char *pwd;
	char *npath;

	pwd = NULL;
	pret = ft_findkey(C_ENV, "PWD");
	pwd = make_good_path(key_value(C_ENV[pret]));
	npath = ft_strjoin(pwd, path);
	ret = chdir(npath);
	if (ret > -1 && pwd && npath)
	{
		if (ft_strcmp(pwd, npath))
			ft_setenv(env, "OLDPWD", pwd);
		ft_setenv(env, "PWD", npath);
		ft_secfree(pwd), ft_secfree(npath);
		return (0);
	}
	check_filerror(npath, path);
	ft_secfree(pwd), ft_secfree(npath);
	return (-1);
}
