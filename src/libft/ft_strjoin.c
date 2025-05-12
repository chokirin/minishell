/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:20:24 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/14 17:39:22 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pnt;
	char	*buff;

	pnt = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (pnt == NULL)
		return (NULL);
	buff = pnt;
	while (*s1)
	{
		*buff = *s1;
		buff++;
		s1++;
	}
	while (*s2)
	{
		*buff = *s2;
		buff++;
		s2++;
	}
	*buff = '\0';
	return (pnt);
}
/*
int main() {
    char *s1 = "Hello, ";
    char *s2 = "World!";
    char *result = ft_strjoin(s1, s2);

    if (result != NULL) {
        printf("Result: %s\n", result);  // 期望输出 "Hello, World!"
        free(result);  // 释放内存
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}
*/
