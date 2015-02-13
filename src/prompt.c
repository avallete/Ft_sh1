/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 12:41:48 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	ft_wait_cmd(t_env *env, char **buf)
{
	static int i = 0;

	if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	read_list(t_cmd *list)
{
	int i;

	while (list)
	{
		i = 0;
		ft_putchar('\n');
		list = list->next;
	}
}

void	ft_init_cmd(t_env *env)
{
	char	*buf;
	char	**pipe;
	t_cmd	*tmp;
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
	read_list(env->cmd);
	if (pipe)
		free_split(pipe);
	if (buf)
		free(buf);
	buf = NULL;
}

void	print_inv(t_env *env)
{
	t_cmd	*tmp;

	ft_putstr("$> ");
	ft_init_cmd(env);
	if (env->cmd)
		free_cmd(env->cmd);
	env->cmd = NULL;
}
