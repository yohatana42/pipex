/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:53:59 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 13:54:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_putnbr(int n, int *result_count)
{
	char	c;

	if (n == -2147483648)
		ft_putstr("-2147483648", result_count);
	else if (n == 0)
		ft_putchar('0', result_count);
	else
	{
		if (n < 0)
		{
			ft_putchar('-', result_count);
			n = n * -1;
		}
		if (n > 9)
			ft_putnbr(n / 10, result_count);
		c = (n % 10) + '0';
		ft_putchar(c, result_count);
	}
}
