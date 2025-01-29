/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:43:06 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 13:47:38 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_putunbr(unsigned int n, int *result_count)
{
	char	c;

	if (n == 0)
		ft_putchar('0', result_count);
	else
	{
		if (n > 9)
			ft_putunbr(n / 10, result_count);
		c = (n % 10) + '0';
		ft_putchar(c, result_count);
	}
}
