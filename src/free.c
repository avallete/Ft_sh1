/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:18:18 by avallete          #+#    #+#             */
/*   Updated: 2015/02/13 12:19:15 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

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
		if (split[i])
			free((split)[i]);
		free(split);
		split = NULL;
	}
}

void	free_arg(t_arg *arg)
{
	if (arg->arg)
		free_split(arg->arg);
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


