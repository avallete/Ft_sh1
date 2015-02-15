#include <ft_sh.h>



void	init_path(t_env *env)
{
	char	*envpath;
	int	i;

	envpath = NULL;
	if (C_CPATH)
		ft_splitdel(C_CPATH);
	i = ft_findkey(C_ENV, "PATH");
	if (i > -1)
	{
		envpath = ft_strdup(C_ENV[i] + 5);
		C_CPATH = ft_strsplit(envpath, ':');
	}
	if (envpath)
		free(envpath), envpath = NULL;
}
