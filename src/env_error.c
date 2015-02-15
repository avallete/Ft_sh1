/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 18:08:26 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 18:51:05 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<ft_sh.h>

void	found_pathrescue(t_env *env)
{
	int fd;
	int ret;
	int i;
	char buf[ENAMETOOLONG];

	i = 0;
	ft_bzero(buf, ENAMETOOLONG);
	ret = -1;
	fd = -1;
	if ((fd = open("/etc/paths", O_RDONLY)) > -1)
		ret = read(fd, buf, ENAMETOOLONG);
	if (ret > -1)
	{
		while (buf[i])
			buf[i] == '\n' ? (buf[i] = ':'), i++ : i++;
		ft_setenv(env, "PATH", buf);
	}
	if (fd > -1)
		close(fd);
}

void	rescue_env(t_env *env)
{
	int i;

	i = 0;
	if (C_ENV)
	{
		if ((i = ft_findkey(env->infos->env, "PATH=")) == -1)
			found_pathrescue(env);
	}
	//	else
	//		create_env(*env);
}


