/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:47:49 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/12 14:14:24 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	length;	

	length = 0;
	while (src[length] != '\0')
		length++;
	if (size == 0)
	{
		return (length);
	}
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (length);
}
/*
int main() {
    const char *src = "Hello, world!";
    char dest[6]; // 目标缓冲区只有 6 个字节

    size_t len = ft_strlcpy(dest, src, sizeof(dest));

    printf("源字符串的长度：%zu\n", len); // 输出源字符串的长度
    printf("目标字符串：%s\n", dest);    // 输出目标字符串

    return 0;
}
*/
