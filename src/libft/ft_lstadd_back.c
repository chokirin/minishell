/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:46:50 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/18 17:25:16 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = *lst;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}
