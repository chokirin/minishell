/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:09:01 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/14 14:18:09 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*t1;
	const unsigned char	*t2;

	if (n == 0)
		return (0);
	i = 0;
	t1 = (const unsigned char *)s1;
	t2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (t1[i] != t2[i])
			return (t1[i] - t2[i]);
		i++;
	}
	return (0);
}
/*
int main() {
    char buffer1[] = "Hello, world!";
    char buffer2[] = "Hello, world!";
    char buffer3[] = "Hello, C!";

    // 比较 buffer1 和 buffer2（相同内容）
    if (ft_memcmp(buffer1, buffer2, sizeof(buffer1)) == 0) {
        printf("buffer1 and buffer2 are equal.\n");
    } else {
        printf("buffer1 and buffer2 are not equal.\n");
    }

    // 比较 buffer1 和 buffer3（不同内容）
    if (ft_memcmp(buffer1, buffer3, sizeof(buffer3)) == 0) {
        printf("buffer1 and buffer3 are equal.\n");
    } else {
        printf("buffer1 and buffer3 are not equal.\n");
    }

    return 0;
}
*/
