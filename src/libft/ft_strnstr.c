/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:09:37 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/13 14:32:01 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == to_find[0])
		{
			j = 1;
			while (to_find[j] != '\0' && str[i + j] == to_find[j]
				&& i + j < len)
				j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main(int argc, char **argv)
{
	if (argc==3)
	{
		char *rslt = ft_strnstr(argv[1], argv[2], 7);
		if (rslt != NULL)
			printf("%s\n", rslt);
		else
			printf("not found\n");
	}
	return 0;
}
*/
