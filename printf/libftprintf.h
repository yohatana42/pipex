/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:25:48 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 16:39:57 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(char c, int *result_count);
void	ft_putnbr(int n, int *result_count);
void	ft_putstr(char *s, int *result_count);
void	ft_putunbr(unsigned int n, int *result_count);
void	ft_puthex(unsigned long long num, int *result_count, char big_flag);
void	ft_putpoint(unsigned long long poi, int *result_count);

#endif
