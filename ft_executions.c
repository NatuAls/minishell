#include "includes/minishell.h"

int ft_strlen_array(char **s) // cuenta las palabras split 
{	
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
	
}
// access ( path , modo  X_OK  significa que  access esta preaguntando al USER si se puede ejecutar )    Si se puede devuelve 0  y si falla devuelve -1
int ft_check_access(char *path)
{

	if (access(path, X_OK) == 0)
		return (1);
	else 
		return (-1);
}

char *ft_get_path(ASTNode*command, t_mini_sh *sh) // intento de refactor
{
	char 	*path;
	char 	**path_splited;
	int	len;
	int	count;
	char 	*to_exec;
	char	*result;
	char	*tmp;

	path = ft_getenv(sh->env, "PATH");
	if (!path)
		return (NULL);
	path_splited = ft_split(path,':');
	count = 0;
	len = ft_strlen_array(path_splited);

	to_exec = ft_strjoin("/", command->args[0]);	
						   
/*	{	 Para ver las string  despues del split con : de delimitador
		int i = 0;
		while (i < len)
		{	printf("*%s*\n\n",path_splited[i]);  i++; }// a eliminar
	 
						
	}                  */ 
	
	
	while (count < len)
	{
		tmp = path_splited[count];
		path_splited[count] = ft_strjoin(path_splited[count], to_exec);
		free(tmp);
		if (ft_check_access(path_splited[count]) == 1)
		{
			
			result = ft_strdup(path_splited[count]);
			ft_free_strs(path_splited);
			free(to_exec);
			return (result);
		}
/*		else  
		{
			free(path_splited[count]);
//			free(**path_splited);
			free(path_splited);
			free(to_exec);

		}              */
		count++;					
	}
	free(to_exec);
	ft_free_strs(path_splited);
	return (NULL);
//	free(to_exec);
//	return (path_splited[count]); // solo para que devuelva algo  
}

void	ft_put_error(char *prefix, char *msg)
{
	write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_execute(ASTNode *node, t_mini_sh *sh)
{
	int	status;
	char 	*path;
	char	**env_arr;

	if (node->type == NODE_COMMAND && !node->args[0][0])
		return ;
	if (ft_execute_builting(node, sh))
		return ;
	sh->mypid = fork();
	if (sh->mypid == -1)
		exit(EXIT_FAILURE);
	else if (sh->mypid == 0)
	{
		ft_setup_own();
		if (node->type == NODE_REDIR)
			node = ft_apply_redirection(node);
		if (!node)
			exit(EXIT_FAILURE);
		if (ft_execute_builting(node, sh))
			exit(EXIT_SUCCESS);
		if(ft_strchr(node->args[0], '/') != NULL)
			path = ft_strdup(node->args[0]);
		else
			path = ft_get_path(node, sh);
		if (!path)
		{
			ft_put_error("Command not found", node->args[0]);
			exit(127); //comando no encontrado
		}
		env_arr = ft_env_to_arr(sh->env);
		if (execve(path, node->args, env_arr) == -1)
		{
			ft_put_error(path, strerror(errno));
			free(path);
			ft_free_strs(env_arr);
			exit(126); //comando no ejecutable
		}
		ft_free_strs(env_arr);
	}
	waitpid(sh->mypid, &status, 0);
	sh->last_status = status >> 8;
}
