/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 15:05:22 by avallete          #+#    #+#             */
/*   Updated: 2015/02/12 18:48:57 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

t_arg	*create_arg(char **args, int nb)
{
	t_arg *arg;

	clear_cmd(*args);
	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->nb = nb;
	arg->pipe = 0;
	arg->vpoint = 0;
	arg->arg = ft_strsplit(*args, ';');
	return (arg);
}

t_cmd	*cmd_new(char **args, int nb)
{
	t_cmd *cmd;

	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->arg = create_arg(args, nb);
	cmd->next = NULL;
	cmd->pipe = NULL;
	return (cmd);
}

void	cmd_pushback(char **args, int nb, t_cmd **cmd)
{
	t_cmd *tmp;

	if (*cmd)
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd_new(args, nb);
	}
	else
		*cmd = cmd_new(args, nb);
}

void	ft_wait_cmd(t_env *env, char **buf, int mode)
{
	static int i = 0;

	if (env->cmd && mode)
	{
		while (env->cmd->pipe)
			env->cmd = env->cmd->pipe;
		if (buf && *buf)
			cmd_pushback(buf, i, &env->cmd->pipe);
	}
	else if (buf && *buf)
		cmd_pushback(buf, i, &env->cmd), i++;
}

void	free_split(char **split)
{
	int i;

	i = 0;
	if (split)
	{
		while ((split)[i])
			i++;
		while (i > 0)
			free((split)[i--]);
		free((split)[i]);
		free(split);
		split = NULL;
	}
}

void	free_pipe(t_cmd *cmd)
{
	if (cmd->pipe)
		free_pipe(cmd->pipe);
	free_split(&cmd->arg->arg);
	free(cmd->pipe);
	cmd->pipe = NULL;
}

void	ft_init_cmd(t_env *env)
{
	char	*buf;
	char	**pipe;
	int		i;

	i = 0;
	pipe = NULL;
	buf = NULL;
//	while (!(get_next_line(0, &buf)))
//		get_next_line(0, &buf);
//	clear_cmd(buf);
	pipe = ft_strsplit("eofk | oeifjwifj | weijfoiwj f| fweoij", '|');
	//	while (pipe[i])
	//		ft_wait_cmd(env, &pipe[i], i), i++;
	free_split(&pipe);
	if (buf)
		free(buf);
	buf = NULL;
}

void	clear_cmd(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

void	print_inv(t_env *env)
{
	t_cmd	*tmp;

	ft_putstr("$> ");
	ft_init_cmd(env);
	/*
	 **tmp = env->cmd;
	 **while (tmp)
	 **{
	 **    ft_putstr(tmp->arg->arg[0]);
	 **    ft_putchar('\n');
	 **    tmp = tmp->next;
	 **}
	 */
	//free_pipe(env->cmd);
}
