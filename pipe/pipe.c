#include "includes/minishell.h"

void ft_execute_pipe(ASTNode *node, t_mini_sh *sh)
{
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;

    pipe(fd);
    if (node->type != NODE_PIPE || !node || !node->left || !node->right )
    {
        printf("Error: NODE_PIPE \n");
        return;
    }
    // Crea el primer proceso hijo
    // que ejecutará el comando a la izquierda del pipe
    // y redirigir su salida estándar al pipe   
  
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork error");
        return;
    }

    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (node->left->type == NODE_PIPE)
            ft_execute_pipe(node->left, sh); //recursivamente si hay multiples pipes
        else
            ft_excecute(node->left, sh);
        exit(EXIT_SUCCESS);
    }

    // Crea el segundo proceso hijo
    // que ejecutará el comando a la derecha del pipe
    // y redirigir su entrada estándar desde el pipe
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork error");
        return;
    }

    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
	if (node->right->type == NODE_PIPE)
	    ft_execute_pipe(node->right, sh);
	else
            ft_excecute(node->right, sh);
        exit(EXIT_SUCCESS);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
