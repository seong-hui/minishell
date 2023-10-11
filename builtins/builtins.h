/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:35:59 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/11 17:38:55 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *s);
void	builtin_echo(char **token);

#endif

