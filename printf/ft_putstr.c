/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:00:29 by yohatana          #+#    #+#             */
/*   Updated: 2024/06/01 17:25:52 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"

void	ft_putstr(char *s, int *result_count)
{
	int	i;

	if (s == NULL)
	{
		ft_putstr("(null)", result_count);
		return ;
	}
	i = 0;
	while (s[i] != 0)
	{
		ft_putchar(s[i], result_count);
		i++;
	}
}
