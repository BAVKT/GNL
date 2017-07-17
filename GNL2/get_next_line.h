/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 09:18:43 by vmercadi          #+#    #+#             */
/*   Updated: 2017/07/05 21:28:29 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GNL_H
# define __GNL_H
# define BUFF_SIZE 100
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
int		rd(t_lst *lst, char **line);
#endif