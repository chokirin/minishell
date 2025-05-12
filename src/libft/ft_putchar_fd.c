/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:23:25 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/16 17:28:47 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
/*
#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 19);
		return (1);
	}
	ft_putchar_fd('B', fd); // 写入到文件中
	close(fd);
	return (0);
}
*/
