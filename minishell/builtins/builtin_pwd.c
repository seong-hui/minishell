/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:16:33 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/19 18:37:34 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_pwd(t_process *process)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n" , pwd);
		free(pwd); //안 터졌을 때. 
	}
}