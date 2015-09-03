/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 11:45:02 by avallete          #+#    #+#             */
/*   Updated: 2015/02/18 13:00:40 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
**Functions in this file init structure of elements
*/

t_arg	*create_arg(char **args, int nb)
{
	t_arg *arg;

	clear_cmd(*args);
	if ((arg = (t_arg*)malloc(sizeof(t_arg))))
	{
		arg->nb = nb;
		if (*args)
			arg->arg = ft_strsplit(*args, ' ');
	}
	return (arg);
}

t_cmd	*cmd_new(char **args, int nb)
{
	t_cmd *cmd;

	if ((cmd = (t_cmd*)malloc(sizeof(t_cmd))))
	{
		cmd->arg = create_arg(args, nb);
		cmd->next = NULL;
		cmd->prec = NULL;
	}
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
		tmp->next->prec = tmp;
	}
	else
		*cmd = cmd_new(args, nb);
}
