/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:24:37 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/15 18:21:43 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pnt;

	i = 0;
	pnt = (unsigned char *)s;
	while (i < n)
	{
		pnt[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main() {
    char buffer[10];

    ft_memset(buffer, 'A', sizeof(buffer) - 1);  // 将每个字节设置为 'A'
    buffer[9] = '\0';  // 确保字符串以空字符结尾

    printf("After memset: %s\n", buffer);  // 输出 "AAAAAAAAA"
    return 0;
}
*/
