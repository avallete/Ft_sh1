/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 17:39:59 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	ft_print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		ft_printf("%s\n", split[i++]);
}

void	read_list(t_env *env, t_cmd *list)
{
	if (list)
	{
		env->infos->father = fork();
		if (env->infos->father > 0)
			execve("/bin/ls", list->arg->arg, env->infos->env);
		if (list->next && env->infos->father == 0)
			read_list(env, list->next);
	}
}

void	ft_init_cmd(t_env *env)
{
	char	*buf;
	char	**pipe;
	int		i;

	i = 0;
	pipe = NULL;
	buf = NULL;
	while (!(get_next_line(0, &buf)))
		get_next_line(0, &buf);
	clear_cmd(buf);
	pipe = ft_strsplit(buf, ';');
	while (pipe[i])
		ft_wait_cmd(env, &pipe[i]), i++;
	if (pipe)
		ft_splitdel(pipe);
	if (buf)
		free(buf);
	buf = NULL;
}

void	print_inv(t_env *env)
{
	ft_putstr("$> ");
	ft_init_cmd(env);
	if (env->infos->father == 0)
		read_list(env, env->cmd);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
