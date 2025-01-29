/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:26:08 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 17:52:26 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_puthex(unsigned long long num, int *result_count, char big_flag)
{
	int		temp;
	char	*use_char;

	if (big_flag == 'X')
		use_char = "0123456789ABCDEF";
	else
		use_char = "0123456789abcdef";
	if (num > 15)
	{
		temp = num % 16;
		num = num / 16;
		ft_puthex(num, result_count, big_flag);
		ft_putchar(use_char[temp], result_count);
	}
	else
		ft_putchar(use_char[num % 16], result_count);
}
