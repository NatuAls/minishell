#include "includes/minishell.h"

void	ft_bexit(t_mini_sh *sh)
{
	int	exit_status;

	exit_status = sh->last_status;
	ft_free_mini_sh(sh, 1);
	rl_clear_history();
	exit(exit_status);
}
