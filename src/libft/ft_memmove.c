/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:27:13 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/15 18:47:40 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (d < s && i < n)
	{
		d[i] = s[i];
		i++;
	}
	while (d >= s && n > 0)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
	return (dest);
}
/*
int main() {
    char str[] = "hello world";
    
    // 使用 memmove 将 "world" 移动到字符串的前部分
    ft_memmove(str, str+6, 5);

    printf("%s\n", str); // 输出: "world world"
    
    return 0;
}
*/
