/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 04:17:26 by vmercadi          #+#    #+#             */
/*   Updated: 2016/11/23 11:25:13 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
	|| (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
