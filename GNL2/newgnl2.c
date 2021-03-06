//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newgnl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 09:18:40 by vmercadi          #+#    #+#             */
/*   Updated: 2017/07/24 15:24:24 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
** Return the block corresponding to the fd. 
** If fd haven't been seen before, create a block.
*/

t_lst 	*crema(int fd, t_lst *lst)
{
		//ft_putendl("1");
	if (lst)
	{
		while (lst)
		{
			if (lst->fd == fd)
				return (lst);
			if (lst->next)
				lst = lst->next;
			else
				break ;
		}
		lst->next = (t_lst *)malloc(sizeof(t_lst));
		lst = lst->next;
	}
	else
		lst = (t_lst *)malloc(sizeof(t_lst));
	lst->fd = fd;
	lst->next = NULL;
	return (lst);
}

/*
** Read fd and fill the line
*/

int		rd(t_lst *lst, char **line)
{
		//ft_putendl("2");
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	
	ret = 1;
	ft_strdel(line);
	*line = ft_strnew(0);
	if (lst->str[0])
	{
		if ((tmp = ft_strchr(lst->str, '\n')))
		{
			*line = ft_strncpy(*line, lst->str, tmp - lst->str);
			ft_strcpy(lst->str, tmp + 1);
			return (1);
		}
		*line = ft_strdup(lst->str);
		ft_bzero(lst->str, BUFF_SIZE);
	}
	while (ret > 0)
	{
		if ((tmp = ft_strchr(*line, '\n')))
		{
			ft_strcpy(lst->str, tmp);		
			*tmp = '\0';
			return (1);
		}
		ret = read(lst->fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		*line = ft_strjoin(*line, buf);
	}
	return (0);
}

/*
** Create list and start the gnl
*/

int		get_next_line(int const fd, char **line)
{
		//ft_putendl("3");
	static t_lst	*firstm;
	t_lst			*lst;

	if (fd == 0 || !line)
		return (-1);
	if (!firstm)
	{
		firstm = crema(fd, firstm);
		lst = firstm;
	}
	else
		lst = crema(fd, firstm);
	return (rd(lst, line));
}

int main (int ac, char **av)
{
	int		fd;
	int		fd2;
	int		fd3;
	char	*line;

	(void)ac;
	line = ft_strnew(0);
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	//ok = get_next_line(fd, &line);
	while(get_next_line(fd, &line))
	{
		ft_putendl(line);
		if (get_next_line(fd2, &line))
			ft_putendl(line);
		if (get_next_line(fd3, &line))
			ft_putendl(line);
	}

	// get_next_line(fd, &line);

	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}