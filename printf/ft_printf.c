/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:18:06 by yohatana          #+#    #+#             */
/*   Updated: 2025/01/17 19:42:17 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

static void	read_str(const char *str, va_list ap, int *result_count);
static void	check_specifier(const char *str, va_list ap, int *result_count);

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		result_count;

	result_count = 0;
	va_start(ap, str);
	read_str(str, ap, &result_count);
	va_end(ap);
	return (result_count);
}

static void	read_str(const char *str, va_list ap, int *result_count)
{
	int	space_flag;

	space_flag = 0;
	while (*str)
	{
		if (*str == '%' || space_flag)
		{
			str++;
			if (*str == ' ')
			{
				if (space_flag == 0)
					ft_putchar(' ', result_count);
				space_flag = 1;
			}
			check_specifier(str, ap, result_count);
		}
		else
		{
			ft_putchar(*str, result_count);
			space_flag = 0;
		}
		str++;
	}
}

static void	check_specifier(const char *str, va_list ap, int *result_count)
{
	if (*str == 'c')
		ft_putchar(va_arg(ap, int), result_count);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(ap, int), result_count);
	else if (*str == 's')
		ft_putstr(va_arg(ap, char *), result_count);
	else if (*str == 'p')
		ft_putpoint(va_arg(ap, unsigned long long), result_count);
	else if (*str == 'u')
		ft_putunbr(va_arg(ap, int), result_count);
	else if (*str == 'x' || *str == 'X')
		ft_puthex(va_arg(ap, unsigned long long), result_count, *str);
	else if (*str == '%')
		ft_putchar('%', result_count);
}
