/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:40:01 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 17:50:54 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_putpoint(unsigned long long poi, int *result_count)
{
	ft_putstr("0x", result_count);
	ft_puthex(poi, result_count, 'x');
}
