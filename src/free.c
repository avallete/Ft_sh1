/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallete <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:18:18 by avallete          #+#    #+#             */
/*   Updated: 2015/02/16 13:56:11 by avallete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

/*
** Check any memory allocated in program
** and free them.
*/

void	free_them_all(t_env *env)
{
	if (env)
	{
		if (C_CPATH)
			ft_splitdel(C_CPATH);
		if (env->cmd)
			free_cmd(env->cmd);
		if (C_ENV)
			ft_splitdel(C_ENV);
	}
}

/*
** This function free arg structure malocated element 
*/

void	free_arg(t_arg *arg)
{
	if (arg->arg)
		ft_splitdel(arg->arg);
	if (arg)
		free(arg);
	arg = NULL;
}

/*
** This function move in all list cmd elements and free them
*/

void	free_cmd(t_cmd *cmd)
{
	if (cmd->next)
		free_cmd(cmd->next);
	if (cmd)
		free_arg(cmd->arg), free(cmd);
	cmd = NULL;
}
