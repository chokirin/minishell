/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:42:20 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/18 21:39:35 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = *lst;
			del(temp->content);
			*lst = temp->next;
			free(temp);
		}
	}
	*lst = NULL;
}
/*
void del_content(void *content)
{
    free(content);
}

int main()
{
    // 创建一个简单的链表
    t_list *node1 = malloc(sizeof(t_list));
    t_list *node2 = malloc(sizeof(t_list));
    t_list *node3 = malloc(sizeof(t_list));
    
    node1->content = ft_strdup("Node 1");
    node1->next = node2;
    
    node2->content = ft_strdup("Node 2");
    node2->next = node3;
    
    node3->content = ft_strdup("Node 3");
    node3->next = NULL;
    
    // 清空链表
    ft_lstclear(&node1, del_content);
    
    // 检查结果
    if (node1 == NULL)
        printf("List cleared successfully\n");
    else
        printf("List not cleared\n");

    return 0;
}
*/