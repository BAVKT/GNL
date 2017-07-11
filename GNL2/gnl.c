/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 09:18:40 by vmercadi          #+#    #+#             */
/*   Updated: 2017/06/23 18:25:56 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

/*
** Because fillstr was too long. Read while it can.
*/

int		rd(t_lst *lst, char **line)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*c;

	while ((ret = read(lst->fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if ((c = ft_strchr(buf, '\n')))
		{
			if (*c + 1)
			{
						ft_putendl(*line);
						ft_putendl(buf);
						ft_putendl("DEBUG");
				*line = ft_strncat(*line, buf, c + 1 - buf);
				lst->str = ft_strjoin(lst->str, c + 1);
			}
			return (1);
		}
		else
		{
			c = ft_strjoin(*line, buf);
			!line ? : ft_strdel(line);
			if (*c)
				*line = c;
		}
	}
	return (0);
}

/*
** Allocate and fill the str
*/

int		fillstr(t_lst *lst, char **line)
{

	char	*c;
	if ((c = ft_strchr(lst->str, '\n')))
	{
		if (*c + 1)
		{
			!line ? : ft_strdel(line);
			*line = ft_strnew(1);
			*line = ft_strncat(*line, lst->str, c + 1 - lst->str);
			ft_strdel(&lst->str);
			lst->str = ft_strdup(c + 1);
		}
		return (1);
	}
	!line ? : ft_strdel(line);
	if (lst->str[0] != '\0')
	{
		*line = ft_strdup(lst->str);
		ft_strdel(&lst->str);
		lst->str = ft_strnew(1);
	}
	if (rd(lst, line))
		return (1);
	return (0);
}

/*
** Return the block corresponding to the fd. 
** If fd haven't been seen before, create a block.
*/

t_lst 	*crema(int fd, t_lst *lst)
{
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	lst = (t_lst *)malloc(sizeof(t_lst));
	lst->fd = fd;
	lst->str = ft_strnew(1);
	lst->next = NULL;
	return (lst);
}

/*
** The legendary get_next_lol
*/

int		get_next_line(const int fd, char **line)
{
	static t_lst	*firstm;
	t_lst 			*lst;
	int				ok;

	if (!firstm)
		firstm = crema(fd, firstm);
	lst = firstm;
	lst = crema(fd, lst);
	ok = fillstr(lst, line);
	if (*line[0] == '\n')
		*line[0] = '\0';
	ft_putstr(*line);
	return (ok);
}

int main (int ac, char **av)
{
	int		i;
	int		fd;
	//int		fd2;
	char	*line;

	(void)ac;
	i = 1;
	line = ft_strnew(1);
	fd = open(av[1], O_RDONLY);
	//fd2 = open(av[2], O_RDONLY);
	while(get_next_line(fd, &line))
		;
	close(fd);
	//while(get_next_line(fd2, &line))
	//	;
	//close(fd2);
	return (0);
}
