/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:31:25 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 11:16:15 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char	check_setenv(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if ((!(ft_strcmp("setenv", *C_CARG(list)))))
	{
		if (ft_splitlen(C_CARG(list)) < 4)
		{
			if (C_CARG(list)[1] == NULL)
				ft_splitprint(C_ENV);
			else if (C_CARG(list)[1] && C_CARG(list)[2])
				ft_setenv(env, C_CARG(list)[1], C_CARG(list)[2]);
			else if (C_CARG(list)[1] && (!(C_CARG(list)[2])))
				ft_setenv(env, C_CARG(list)[1], "");
		}
		else
			ETOOMANYARG("setenv");
		ret = 1;
	}
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

char	check_unsetenv(t_env *env, t_cmd *list)
{
	char ret;
	int	i;

	i = 1;
	ret = 0;
	if (!(ft_strcmp("unsetenv", *C_CARG(list))))
	{
		if (C_CARG(list)[1] == NULL)
			ETOOFEWARG("unsetenv");
		else
			while (C_CARG(list)[i])
				ft_unsetenv(env, C_CARG(list)[i++]);
		ret = 1;
	}
	return (ret);
}

char	check_exit(t_env *env, t_cmd *list)
{
	char	ret;
	int	e;

	ret = 0;
	e = 0;
	if (list)
	{
		if (!(ft_strcmp("exit", *C_CARG(list))))
		{
			if (C_CARG(list)[1])
				ETOOMANYARG("exit");
			else
			{
				C_CARG(list)[1] ? (e = ft_atoi(C_CARG(list)[1]))
					: (e = 0);
				free_them_all(env);
				exit(e);
			}
			ret = 1;
		}
	}
	return (ret);
}

int	check_access(char *path)
{
	DIR *dir;

	if (path)
	{
		dir = opendir(path);
		if (dir != NULL)
			return (1);
		if (dir)
			closedir(dir);
	}
	return (0);
}

char	*key_value(char *env)
{
	int i;

	i = 0;
	while (env[i] != '=' && env[i] != '\0')
		i++;
	i++;
	if (env[i])
		return (ft_strdup(env + i));
	else
		return (ft_strdup(""));
}

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
		ft_setenv(env, "OLDPWD", pwd);
		ft_setenv(env, "PWD", path);
		free(pwd);
		return (0);
	}
	return (-1);
}

int	change_relrep(t_env *env, char *path)
{
	int ret;
	int pret;
	char *pwd;
	char *npath;

	pwd = NULL;
	pret = ft_findkey(C_ENV, "PWD");
	if (pret > -1)
		pwd = key_value(C_ENV[pret]);
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

void	go_oldpwd(t_env *env)
{
	int oldpwd;
	char *oldpwdval;

	oldpwd = -1;
	oldpwdval = NULL;
	oldpwd = ft_findkey(C_ENV, "OLDPWD");
	if (oldpwd > -1)
		oldpwdval = key_value(C_ENV[oldpwd]);
	if (oldpwdval)
		change_absrep(env, oldpwdval), free(oldpwdval), oldpwdval = NULL;
}

void	go_home(t_env *env)
{
	int	home;
	char *homeval;

	homeval = NULL;
	home = -1;
	home = ft_findkey(C_ENV, "HOME");
	if (home > -1)
		homeval = key_value(C_ENV[home]);
	if (homeval)
		change_absrep(env, homeval), free(homeval), homeval = NULL;
}

char	check_cd(t_env *env, t_cmd *list)
{
	char	ret;

	ret = 0;
	if (list)
	{
		if (!(ft_strcmp("cd", *C_CARG(list))))
		{
			if (C_CARG(list)[1])
			{
				if ((!(ft_strcmp(C_CARG(list)[1], "-"))))
					go_oldpwd(env);
				else if (C_CARG(list)[1][0] != '/')
					change_relrep(env, C_CARG(list)[1]);
				else
					change_absrep(env, C_CARG(list)[1]);
			}
			else
				go_home(env);
			ret = 1;
		}
	}
	return (ret);
}

char	check_builtin(t_env *env, t_cmd *list)
{
	char ret;

	ret = 0;
	if (list)
	{
		if ((ret = check_exit(env, list)))
			return (ret);
		else if ((ret = (check_env(env, list))))
			return (ret);
		else if ((ret = (check_setenv(env, list))))
			return (ret);
		else if ((ret = (check_unsetenv(env, list))))
			return (ret);
		else
			ret = check_cd(env, list);
	}
	return (ret);
}
