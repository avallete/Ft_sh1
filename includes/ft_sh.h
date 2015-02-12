#ifndef FT_SH_H
# define FT_SH_H
# include <libft.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

typedef	struct		s_arg
{
	char			**arg;
	int				nb;
	char			pipe;
	char			vpoint;
}					t_arg;

typedef	struct		s_cmd
{
	t_arg			*arg;
	struct s_cmd	*next;
	struct s_cmd	*pipe;
}					t_cmd;

typedef struct		s_inf
{
	char			**env;
}					t_inf;

typedef struct		s_env
{
	t_cmd			*cmd;
	t_inf			*infos;
}					t_env;

/*
** prompt
*/

void	free_split(char **split);
void	ft_wait_cmd(t_env *env, char **buf, int mode);
void	ft_init_cmd(t_env *env);
void	clear_cmd(char *str);
void	print_inv(t_env *env);
#endif
