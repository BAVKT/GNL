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
#include <stdio.h>

/*
** Return the block corresponding to the fd. 
** If fd haven't been seen before, create a block.
*/

t_lst 	*crema(int fd, t_lst *lst)
{
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
char	*biggerbuf(int const fd, char *buf, int *ret)
{
	char	tmp[BUFF_SIZE + 1];

	*ret = read(fd, tmp, BUFF_SIZE);
	tmp[*ret] = '\0';
	buf = ft_strjoin(buf, tmp);
	return (buf);
}

int get_next_line(int const fd, char ** line)
{
	static char	*buf = "";
	int			ret;
	char		*str;

	if (!line || fd <= 0)
		return (-1);
	ret = 1;
	if (buf[0] == '\0')
		buf = ft_strnew(0);
	while (ret > 0)
	{
		if ((str = ft_strchr(buf, '\n')) != NULL)
		{
			*str = '\0';
			*line = ft_strdup(buf);
			ft_memmove(buf, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
	buf = biggerbuf(fd, buf, &ret);
	}
	return (ret);
}
*/
/*
//		MARCHE EN UNE FONCTION
int		get_next_line(int const fd, char **line)
{
	static char	*buf = "";
	int			ret;
	char		*str;
	char		tmp[BUFF_SIZE + 1];

	if (!line || fd <= 0)
		return (-1);
	ret = 1;
	if (buf[0] == '\0')
		buf = ft_strnew(0);
	while (ret > 0)
	{
		if ((str = ft_strchr(buf, '\n')) != NULL)
		{
			*str = '\0';
			*line = ft_strdup(buf);
			ft_memmove(buf, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
		ret = read(fd, tmp, BUFF_SIZE);
		tmp[ret] = '\0';
		buf = ft_strjoin(buf, tmp);
	}
	return (ret);
}
*/
// Une fonction marche addapté perso
// int		get_next_line(int const fd, char **line)
// {
// 	static t_lst	*firstm;
// 	t_lst			*lst;
// 	int				ret;
// 	char			*str;
// 	char			tmp[BUFF_SIZE + 1];

// 	if (!line || fd <= 0)
// 		return (-1);
// 	if (fd == 0 || !line)
// 		return (-1);
// 	if (!firstm)
// 	{
// 		firstm = crema(fd, firstm);
// 		lst = firstm;
// 	}
// 	else
// 		lst = crema(fd, firstm);
// 	ret = 1;
// 	if (lst->str[0] == '\0')
// 		lst->str = ft_strnew(0);
// 	while (ret > 0)
// 	{
// 		if ((str = ft_strchr(lst->str, '\n')) != NULL)
// 		{
// 			*str = '\0';
// 			*line = ft_strdup(lst->str);
// 			ft_memmove(lst->str, str + 1, ft_strlen(str + 1) + 1);
// 			return (1);
// 		}
// 		ret = read(fd, tmp, BUFF_SIZE);
// 		tmp[ret] = '\0';
// 		lst->str = ft_strjoin(lst->str, tmp);
// 	}
// 	return (ret);
// }


int		rd(t_lst *lst, char **line)
{
	int		ret;
	char	tmp[BUFF_SIZE + 1];
	char	*str;
	
	ret = 1;
	while (ret > 0)
	{
		if ((str = ft_strchr(lst->str, '\n')))
		{
			*str = '\0';
			!*line ? : ft_strdel(line);
			*line = ft_strdup(lst->str);
			ft_memmove(lst->str, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
		ret = read(lst->fd, tmp, BUFF_SIZE);
		tmp[ret] = '\0';
		lst->str = ft_strjoin(lst->str, tmp);
	}
	!*line ? : ft_strdel(line); 
	*line = ft_strdup(lst->str);
	return (0);
}


int		get_next_line(int const fd, char **line)
{
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
	if (lst->str[0] == '\0')
		lst->str = ft_strnew(0);
	return (rd(lst, line));
}


int main (int ac, char **av)
{
	int		fd;
	int		fd2;
	//int		fd3;
	char	*line;

	(void)ac;
	line = ft_strnew(0);
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	//fd3 = open(av[3], O_RDONLY);
	//ok = get_next_line(fd, &line);
	while(get_next_line(fd, &line))
	{
		ft_putendl(line);
		get_next_line(fd2, &line);
		ft_putendl(line);
		//get_next_line(fd3, &line);
		//ft_putendl(line);
	}

	// get_next_line(fd, &line);
	ft_putendl(line);		
	close(fd);
	close(fd2);
	//close(fd3);
	while (1)
		;
	return (0);
}