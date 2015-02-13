/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:18:18 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 17:37:38 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	free_arg(t_arg *arg)
{
	if (arg->arg)
		ft_splitdel(arg->arg);
	if (arg)
		free(arg);
	arg = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->next)
		free_cmd(cmd->next);
	if (cmd)
		free_arg(cmd->arg), free(cmd);
	cmd = NULL;
}


