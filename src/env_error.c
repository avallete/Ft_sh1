/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 18:08:26 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 11:11:07 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<ft_sh.h>

void	found_pathrescue(t_env *env)
{
	int fd;
	int ret;
	int i;
	char buf[PATH_MAX];

	i = 0;
	ft_bzero(buf, PATH_MAX);
	ret = -1;
	fd = -1;
	if ((fd = open("/etc/paths", O_RDONLY)) > -1)
		ret = read(fd, buf, PATH_MAX);
	if (ret > -1)
	{
		while (buf[i])
			buf[i] == '\n' ? (buf[i] = ':'), i++ : i++;
		ft_setenv(env, "PATH", buf);
	}
	ft_bzero(buf, PATH_MAX);
	if (fd > -1)
		close(fd);
}

void	found_pwdrescue(t_env *env)
{
	char buf[PATH_MAX + 1];

	if (!(getcwd(buf, PATH_MAX)))
		ENAMETOOLON("PWD");
	else
		ft_setenv(env, "PWD", buf);
}

void	found_homerescue(t_env *env)
{
	struct passwd *home;
	char			*homepath;

	home = getpwuid(getuid());
	homepath = ft_strdup(home->pw_dir);
	if (homepath)
		ft_setenv(env, "HOME", homepath), free(homepath);
}

void	found_usernamerescue(t_env *env)
{
	struct passwd *home;
	char		*name;

	home = getpwuid(getuid());
	name = ft_strdup(home->pw_name);
	if (name)
		ft_setenv(env, "USERNAME", name), free(name);
}

void	rescue_env(t_env *env)
{
	int i;

	i = 0;
	if (C_ENV)
	{
		if ((i = ft_findkey(env->infos->env, "PATH")) == -1)
			found_pathrescue(env);
		if ((i = ft_findkey(env->infos->env, "PWD")) == -1)
			found_pwdrescue(env);
		if ((i = ft_findkey(env->infos->env, "HOME")) == -1)
			found_homerescue(env);
		if ((i = ft_findkey(env->infos->env, "USERNAME")) == -1)
			found_usernamerescue(env);
	}
}


