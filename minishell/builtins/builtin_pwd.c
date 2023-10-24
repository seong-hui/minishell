/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:16:33 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 21:11:50 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n" , pwd);
		free(pwd); //안 터졌을 때. 
	}
	return;
}