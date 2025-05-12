/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:26:26 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/15 20:19:31 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (s[i])
	{
		if ((unsigned char)s[i] == uc)
			return ((char *)&s[i]);
		i++;
	}
	if (uc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main()
{
    const char *str = "teste";
    char *result = ft_strchr(str, 1024);
    if (result)
        printf("Found character at: %s\n", result);
    else
        printf("Character not found.\n");

    return 0;
}
*/
