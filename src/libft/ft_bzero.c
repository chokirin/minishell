/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:42:58 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/15 09:31:58 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*pnt;

	i = 0;
	pnt = (unsigned char *)s;
	while (i < n)
	{
		pnt[i] = '\0';
		i++;
	}
}
/*
int main() {
    char buffer[10] = "Hello";

    printf("Before bzero: %s\n", buffer);
    bzero(buffer, sizeof(buffer));  // 清零整个 buffer

    printf("After bzero: %s\n", buffer);  // buffer内容清空，输出为空
    return 0;
}
*/
