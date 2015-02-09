#ifndef FT_SH_H
# define FT_SH_H
# include <libft.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
typedef	struct		s_cmd
{
	char			**arg;
	int				nb;
}					t_cmd;

typedef	struct		s_env
{
	t_cmd			cmd;
}					t_env;
#endif
