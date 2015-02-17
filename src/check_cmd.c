#include <ft_sh.h>

char	*find_commande(t_env *env, char *cmd)
{
	int i;
	char *tmp;
	char *good_path;

	tmp = NULL;
	i = 0;
	good_path = NULL;
	if (C_CPATH)
	{
		while (C_CPATH[i] && *C_CPATH[i])
		{
			good_path = ft_strjoin(C_CPATH[i], "/");
			tmp = ft_strjoin(good_path, cmd);
			if (tmp && access(tmp, X_OK) > -1)
			{
				ft_secfree(good_path);
				return (tmp);
			}
			else
				ft_secfree(tmp), ft_secfree(good_path);
			i++;
		}
	}
	return (NULL);
}

void	check_cmd(t_env *env, t_cmd *list)
{
	char *pathcmd;

	pathcmd = NULL;
	if (list && C_CARG(list) && *C_CARG(list))
	{
		if ((pathcmd = find_commande(env, C_CARG(list)[0])))
		{
			env->infos->father = fork();
			if (!(check_toolongarg(C_CARG(list))))
			{
				if (env->infos->father > 0)
					wait(NULL);
				if (env->infos->father == 0)
					execve(pathcmd, C_CARG(list), C_ENV);
				ft_secfree(pathcmd);
			}
		}
		else
			EINVALCMD(C_CARG(list)[0]);
	}
}

void	read_list(t_env *env, t_cmd *list)
{
	char ret;

	ret = 1;
	rescue_env(env);
	init_path(env);
	if (list)
	{
		ret = check_builtin(env, list);
		if (ret < 1)
			check_cmd(env, list);
		if (list->next)
			read_list(env, list->next);
	}
}
