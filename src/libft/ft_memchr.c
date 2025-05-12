/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:48:48 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/13 16:59:58 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pnt;

	i = 0;
	pnt = (unsigned char *)s;
	while (i < n)
	{
		if (pnt[i] == (unsigned char)c)
			return (&pnt[i]);
		i++;
	}
	return (NULL);
}
/*
int main()
{
    char str[] = "Hello, world!";
    char *result = ft_memchr(str, 'o', sizeof(str));

    if (result != NULL)
        printf("Found 'o' at position: %ld\n", result - str);
    else
        printf("'o' not found\n");

    return 0;
}
*/
