/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:11:02 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/16 16:40:07 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*pnt;

	i = 0;
	pnt = malloc(ft_strlen(s) + 1);
	if (pnt == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		pnt[i] = f(i, s[i]);
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
