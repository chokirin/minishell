/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:43:23 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/14 18:36:37 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trim(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*pnt;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	while (i > 0 && is_trim(s1[i - 1], set))
		i--;
	j = 0;
	while (j < i && is_trim(s1[j], set))
		j++;
	pnt = malloc(i - j + 1);
	if (pnt == NULL)
		return (NULL);
	k = 0;
	while (k < i - j)
	{
		pnt[k] = s1[j + k];
		k++;
	}
	pnt[k] = '\0';
	return (pnt);
}
/*
int main()
{
    char *s1 = "   Hello, World!   ";
    char *set = "x H";
    char *result = ft_strtrim(s1, set);

    if (result != NULL) {
        printf("Result: '%s'\n", result);  // 期望输出 "Hello, World!"
        free(result);  // 释放内存
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}
*/
