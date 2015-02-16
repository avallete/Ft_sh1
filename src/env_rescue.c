/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_rescue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/16 14:46:41 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 14:46:42 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** Functions for grep a alternative env no env is set
*/

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
		ft_setenv(env, "USER", name), free(name);
}

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


