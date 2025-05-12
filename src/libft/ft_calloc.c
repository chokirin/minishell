/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <haiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:40:06 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/22 17:30:48 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*pnt;
	size_t			i;

	if (nmemb > ((size_t) - 1) / size)
		return (NULL);
	pnt = malloc(nmemb * size);
	if (pnt == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		pnt[i] = 0;
		i++;
	}
	return ((void *)pnt);
}
/*
int main() {
    int *arr;
    size_t num_elements = 5;

    // 使用 calloc 分配 5 个整数的内存，并初始化为零
    arr = (int *)ft_calloc(num_elements, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 打印每个元素的值，应该都是 0
    for (size_t i = 0; i < num_elements; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    // 使用完毕后释放内存
    free(arr);

    return 0;
}
*/
