#ifndef FT_SH_H
# define FT_SH_H
# include <libft.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>

/*
**	Cast macro for more easy access of struct elements
*/

# define SIZE_ENV	(env->infos->size_env)
# define C_ENV		env->infos->env
# define C_EARG		env->cmd->arg->arg
# define C_CARG(x)		x->arg->arg
# define C_CPATH		env->infos->paths

/*
**	ERROR macro
*/

# define ENAMEFORM(x) (ft_putsterr(x), ft_putsterr(":"))
# define ETOOMANYARG(x) (ENAMEFORM(x), ft_puterrdl(" Too many arguments."))
# define ETOOFEWARG(x) (ENAMEFORM(x), ft_puterrdl(" Too few arguments."))
# define ENAMETOOLON(x) (ENAMEFORM(x), ft_puterrdl(" File name too long."))
# define EPATHTOOLON(x) (ENAMEFORM(x), ft_puterrdl(" Path name too long."))


typedef	struct		s_arg
{
	char			**arg;
	int				nb;
}					t_arg;

typedef	struct		s_cmd
{
	t_arg			*arg;
	struct s_cmd	*next;
	struct s_cmd	*prec;
}					t_cmd;

typedef struct		s_inf
{
	char			**env;
	size_t			size_env;
	char			**paths;
	pid_t			father;
}					t_inf;

typedef struct		s_env
{
	t_cmd			*cmd;
	t_inf			*infos;
}					t_env;

/*
** prompt
*/
void	ft_wait_cmd(t_env *env, char **buf);
void	ft_init_cmd(t_env *env);
void	clear_cmd(char *str);
void	print_inv(t_env *env);

/*
** create_cmd
*/

t_arg	*create_arg(char **args, int nb);
t_cmd	*cmd_new(char **args, int nb);
void	cmd_pushback(char **args, int nb, t_cmd **cmd);

/*
** free
*/
void	free_arg(t_arg *arg);
void	free_cmd(t_cmd *cmd);
void	free_them_all(t_env *env);

/*
**clear commandes
*/

void	clear_cmd(char *str);

/*
**set_env
*/

char	**copy_env(char **env, size_t size);
void	ft_setenv(t_env *env, char *key, char *value);
void	ft_recreatenv(t_env *env, char *str);

/*
** unset env
*/
void	ft_unsetenv(t_env *env, char *key);
int		ft_findkey(char **tab, char *str);

/*
** Env rescue
*/
void	found_pathrescue(t_env *env);
void	rescue_env(t_env *env);

/*
** Buitins
*/
char	check_builtin(t_env *env, t_cmd *list);
char	check_env(t_env *env, t_cmd *list);
char	check_setenv(t_env *env, t_cmd *list);

/*
** Errors
*/
char	check_toolongarg(char **cmd);
char	*format_envval(char *key, char *value);

/*
** Path sort/create/format/research
*/
void	init_path(t_env *env);
#endif
