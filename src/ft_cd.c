/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 13:22:23 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 13:53:16 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** This function grep a absolute pathname, check if it's OK
** Go them and edit PWD and OLDPWD value in env if OK
** Else she prompt a error and return a error.
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
		free(npath);
		free(pwd);
		return (0);
	}
	return (-1);
}
