/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:23:08 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/14 15:49:42 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	char	*buff;
	int		src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dest = (char *)malloc(sizeof(*src) * (src_len + 1));
	if (dest == NULL)
		return (NULL);
	buff = dest;
	while (*src != '\0')
	{
		*buff = *src;
		buff++;
		src++;
	}
	*buff = '\0';
	return (dest);
}
/*
int main(void)
{
	char str1[11]="helloworld";
	char *str2 =  ft_strdup(str1);
	printf("%s\n", str2);
	free(str2);
	return 0;
}
*/
