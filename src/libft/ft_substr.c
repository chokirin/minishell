/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:31 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/15 17:58:32 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*pnt;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	pnt = malloc(len + 1);
	if (pnt == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		pnt[i] = s[start + i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
/*
int main() {
    // 测试用例 1: 正常情况
    char *s1 = "Hello, World!";
    char *substr1 = ft_substr(s1, 7, 5);  // 从索引 7 开始，取 5 个字符
    printf("Test 1: %s\n", substr1);  // 应该输出 "World"
    free(substr1);  // 释放内存

    // 测试用例 2: `start` 超过字符串长度
    char *substr2 = ft_substr(s1, 20, 5);  // start 大于字符串长度
    printf("Test 2: %s\n", substr2);  // 应该输出空字符串
    free(substr2);  // 释放内存

    // 测试用例 3: `len` 为 0
    char *substr3 = ft_substr(s1, 0, 0);  // len 为 0
    printf("Test 3: %s\n", substr3);  // 应该输出空字符串
    free(substr3);  // 释放内存

    // 测试用例 4: `start` 小于字符串长度，但 `len` 超过剩余的字符数
    char *substr4 = ft_substr(s1, 7, 100);  // 从索引 7 开始，取 100 个字符（超出长度）
    printf("Test 4: %s\n", substr4);  // 应该输出 "World!"
    free(substr4);  // 释放内存

    // 测试用例 5: `start` 为 0，`len` 正常
    char *substr5 = ft_substr(s1, 0, 5);  // 从索引 0 开始，取 5 个字符
    printf("Test 5: %s\n", substr5);  // 应该输出 "Hello"
    free(substr5);  // 释放内存

    return 0;
}
*/
