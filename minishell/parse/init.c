/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:13:32 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/14 22:13:35 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	init_parse(t_parse *parse, char *str)
{
	parse->cmd = str;
	parse->len = 0;
	parse->idx = 0;
	parse->quote = 0;
}
