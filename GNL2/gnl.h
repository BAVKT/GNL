/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 09:18:43 by vmercadi          #+#    #+#             */
/*   Updated: 2017/06/20 19:40:59 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GNL_H
# define __GNL_H
# define BUFF_SIZE 1
# include "libft/libft.h"

typedef struct		s_lst
{
	int				fd;
	char			*str;
	struct s_lst	*next;
}					t_lst;

int		fillstr(t_lst *lst, char **line);
t_lst 	*crema(int fd, t_lst *lst);
int		get_next_line(const int fd, char **line);
#endif