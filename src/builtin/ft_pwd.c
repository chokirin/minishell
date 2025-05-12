/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:40:07 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 16:40:10 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/builtin.h"

/* pwd with no option: print the current dir
	- no need of args
	- if getcwd(path, size) works
        - print the current working dir path
	    - return 0
    - else
		- print error msg & return 1
*/
void	ft_pwd(char **args, t_env *env)
{
	char	cwd[1024];

	(void)args;
	(void)env;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}
/*
// === testing pwd ===
int main(void)
{
    char *args1[] = {NULL};
    ft_pwd(args1);

    char *args2[] = {"pwd", "arg1", "arg2", NULL};
    ft_pwd(args2);

    chdir("..");
    char *args3[] = {"pwd", "arg1", "arg2", NULL};
    ft_pwd(args3);
}*/
