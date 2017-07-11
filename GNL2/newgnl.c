/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newgnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 09:18:40 by vmercadi          #+#    #+#             */
/*   Updated: 2017/07/05 22:10:02 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Problemes de strdel a moultes endroits moi pas comprendre moi faire LS
**
*/

int		rd(t_lst *lst, char **line)
{
			ft_putendl("rd();");
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*c;

	while ((ret = read(lst->fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if ((c = ft_strchr(buf, '\n')) && c + 1)
		{
			*line = ft_strncat(*line, buf, c + 1 - buf);
			!lst->str[0] ? : ft_strdel(&lst->str);
			lst->str = ft_strnew(0);
			lst->str = ft_strjoin(lst->str, c + 1);
			return (1);
		}
		else
		{
			c = ft_strjoin(*line, buf);
			!line ? : ft_strdel(line);
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
			ft_putendl("fillstr");
	char	*c;

	!line ? : ft_strdel(line);
	*line = ft_strnew(0);
	if ((c = ft_strchr(lst->str, '\n')) && c + 1)	
	{
		*line = ft_strncpy(*line, lst->str, c + 1 - lst->str);
		lst->str = ft_strdup(c + 1);
		return (1);
	}
	if (lst->str[0])
	{
		*line = ft_strdup(lst->str);
		ft_strdel(&lst->str);
		lst->str = ft_strnew(0);
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
			ft_putendl("crema");
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
	lst->str = ft_strnew(0);
	lst->next = NULL;
	return (lst);
}

/*
** The legendary get_next_lol
*/

int		get_next_line(const int fd, char **line)
{
			//ft_putendl("get_next_line");
	static t_lst	*firstm;
	t_lst 			*lst;
	int				ok;

	if (fd == -1)
		return (-1);
	if (!firstm)
	{
		firstm = crema(fd, firstm);
		lst = firstm;
	}
	else
		lst = crema(fd, firstm);


	ok = fillstr(lst, line);
	if (*line[0] == '\n')
		*line[0] = '\0';
	ft_putstr(*line);

	return (ok);
}


int main (int ac, char **av)
{
	int		fd;

	int		ok;
	char	*line;

	(void)ac;
	line = ft_strnew(1);
	fd = open(av[1], O_RDONLY);
	ok = get_next_line(fd, &line);
	while(get_next_line(fd, &line))
		;
	close(fd);

	return (0);
}