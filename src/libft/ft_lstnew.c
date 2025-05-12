/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:45:47 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/18 15:40:37 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pnt;

	pnt = malloc(sizeof(t_list));
	if (pnt == NULL)
		return (NULL);
	pnt->content = content;
	pnt->next = NULL;
	return (pnt);
}
