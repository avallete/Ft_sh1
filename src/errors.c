/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:25:05 by avallete          #+#    #+#             */
/*   Updated: 2015/02/14 15:26:55 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char	check_toolongarg(char **cmd)
{
	int i;
	char err;

	i = 0;
	err = 0;
	while (cmd[i])
	{
		if (ft_strlen(cmd[i]) >= ENAMETOOLONG)
			ENAMETOOLON(cmd[i]), err = 1;
		i++;
	}
	return (err);
}

char	*format_envval(char *key, char *value)
{
	char *tmp;
	char *join;
	size_t keylen;
	size_t vallen;

	(vallen = ft_strlen(value)) >= ENAMETOOLONG ? ENAMETOOLON(value) : 0;
	join = ft_strjoin(key, "=");
	(keylen = ft_strlen(join)) >= ENAMETOOLONG ? ENAMETOOLON(key) : 0;
	tmp = join;
	join = ft_strjoin(join, value);
	free(tmp);
	if (vallen >= ENAMETOOLONG || keylen >= ENAMETOOLONG)
		free(join), join = NULL;
	else if (keylen + vallen >= PATH_MAX)
		EPATHTOOLON(join), free(join), join = NULL;
	return (join);
}
