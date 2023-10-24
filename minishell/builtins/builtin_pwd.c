/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:16:33 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 21:04:58 by jooypark         ###   ########seoul.kr  */
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