
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdio.h>

#define PYPE 3
#define BREAK 2
#define END 1
typedef struct s_stack
{
    char **arg;
    int size;
    int type;
    int fd[2];
    struct s_stack *prev;
    struct s_stack *next;
} t_stack;

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return (i);
}
void lst_add_back(t_stack **stack, t_stack *new)
{
    t_stack *tmp;
    tmp = *stack;
    
    if(!*stack)
    {
        *stack = new;
        return ;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    
}
char *ft_strdup(char *str)
{
    int i = ft_strlen(str);
    char *ret;
    ret = malloc(sizeof(char) * i + 1);
    i = 0;
    while(str[i])
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

int arg_size(char **av)
{
    int i = 0;
    while(av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
        i++;
    return (i);
}

void   ft_exit_fatal(void)
{
    write(2, "error: fatal\n", 13);
    exit(EXIT_FAILURE);
}

int ft_check_for_type(char *str)
{
    if (!str)
        return (BREAK);
    if(!strcmp(str, ";"))
        return (END);
    else 
        return (PYPE);

}
void exec_cmd(t_stack *stack, char **env)
{
    t_stack *temp;

    temp = stack;
    while(temp)
    {
        if(!strcmp(temp->arg[0], "cd"))
        {
            if(temp->size < 2)
            {
                write(2, "error: cd: bad arguments\n", 25);
            }
            else if(chdir(temp->arg[1]) == -1)
            {
                write(2, "error: cd: cannot change directory to ", 39);
                write(2, temp->arg[1], ft_strlen(temp->arg[1]));
                write(2, "\n", 1);
            }
        }
        else
        {
            pid_t pid;
            int status;
            int pipe_open;

            pipe_open = 0;
            if(temp->type == PYPE || (temp->prev && temp->prev->type == PYPE))
            {
                if(pipe(temp->fd) == -1)
                    ft_exit_fatal();
                pipe_open = 1;
            }
            pid = fork();
            if(pid < 0)
                ft_exit_fatal();
            else if(pid == 0)
            {
                if(temp->type == PYPE && dup2(temp->fd[1], 1) < 0)
                    ft_exit_fatal();
                if(temp->prev && temp->prev->type == PYPE && dup2(temp->prev->fd[0], 0) < 0)
                    ft_exit_fatal();
                if(execve(temp->arg[0], temp->arg, env) == -1)
                {
                    write(2, "error: cannot execute ", 22);
                    write(2, temp->arg[0], ft_strlen(temp->arg[0]));
                    write(2, "\n", 1);
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
            }
            else{
                waitpid(pid, &status, 0);
                if(pipe_open)
                {
                    close(temp->fd[1]);
                    if(!temp->next || temp->next->type == BREAK)
                        close(temp->fd[0]);
                    if(temp->prev && temp->prev->type == PYPE)
                        close(temp->prev->fd[0]);
                }
            }
        }
        temp = temp->next;
    }
}

int pars(char **av, t_stack **stack)
{
    t_stack *new;
    
    int size = arg_size(av);
    if(!(new = malloc(sizeof(t_stack))))
        ft_exit_fatal();
    if(!(new->arg = malloc(sizeof(char *) * (size + 1))))
        ft_exit_fatal();
    new->size = size;
    new->next = NULL;
    new->prev = NULL;
    new->arg[size] = NULL;
    while(size--)
        new->arg[size] = ft_strdup(av[size]);
    new->type = ft_check_for_type(av[new->size]);
    lst_add_back(stack, new);
    return (new->size);
}

void ft_free(t_stack *stack)
{
    t_stack *tmp;
    while(stack)
    {
        tmp = stack->next;
        while(stack->size--)
            free(stack->arg[stack->size]);
        free(stack->arg);
        free(stack);
        stack = tmp;
    }
    free(stack);
}

int main(int ac , char **av, char **env)
{
    t_stack *stack;
    if (ac > 1)
    {
        int i = 1;
        while(av[i])
        {
            if (strcmp(av[i], ";") == 0)
            {
                i++;
                continue;
            }
            i += pars(&av[i], &stack);
            if(!av[i])
                break ;
            i++;
        }
        if (stack)
            exec_cmd(stack, env);
        ft_free(stack);
    }
}