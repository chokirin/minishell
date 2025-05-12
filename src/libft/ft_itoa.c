/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:25:58 by haiwang           #+#    #+#             */
/*   Updated: 2024/11/16 15:42:15 by haiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	my_put_nbr(char *a, int n, int n_len, int neg_sign)
{
	int	i;

	i = 0;
	while (i < n_len + neg_sign)
	{
		a[n_len - i + neg_sign -1] = '0' + (n % 10);
		n = n / 10;
		i++;
	}
	a[i] = '\0';
	if (neg_sign)
		a[0] = '-';
}

char	*ft_itoa(int n)
{
	int		neg_sign;
	int		n_len;
	char	*a;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg_sign = 0;
	if (n < 0)
	{
		neg_sign = 1;
		n = -n;
	}
	n_len = get_len(n);
	a = malloc(neg_sign + n_len + 1);
	if (a == NULL)
		return (NULL);
	my_put_nbr(a, n, n_len, neg_sign);
	return (a);
}
/*
int main()
{
	int x = -12345;
	printf("%s\n", ft_itoa(x));
	return 0;
}
*/
