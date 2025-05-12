/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:15:10 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/12 14:34:27 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	i = 0;
	destlen = 0;
	while (dest[destlen])
		destlen++;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (destlen >= size)
		return (srclen + size);
	while ((destlen + i < size - 1) && (src[i] != '\0'))
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (srclen + destlen);
}
/*
int main() {
    char dest[15] = "Hello";
    const char *src = " World!";
    size_t size = 15;

    size_t result = ft_strlcat(dest, src, size);

    printf("目标字符串: %s\n", dest);
    printf("源字符串长度: %zu\n", result);
    
    return 0;
}
*/
