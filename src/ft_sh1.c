#include <ft_sh.h>

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

char	**ft_wait_cmd(void)
{
	char	*buf;

	while (!(get_next_line(1, &buf)))
		get_next_line(1, &buf);
	clear_cmd(buf);
	return (ft_strsplit(buf, ' '));
}

void	ft_init_cmd(t_env *env)
{
	int e;

	e = 0;
	env->cmd.arg = ft_wait_cmd();
	while (env->cmd.arg[e])
		e++;
	env->cmd.nb = e;
}

void	print_inv(void)
{
	t_env env;
	int		e;

	e = 0;
	ft_putstr("$> ");
	ft_init_cmd(&env);
	while (env.cmd.arg[e])
	{
		ft_putendl(env.cmd.arg[e]);
		e++;
	}
}

int		main(void)
{
	while (1)
	{
		print_inv();
	}
	return (0);
}
