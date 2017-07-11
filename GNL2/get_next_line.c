/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
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
				//ft_putendl("rd();");
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*c;

	while ((ret = read(lst->fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
					//ft_putstr("BUF = ");
					//ft_putendl(buf);
					//ft_putendl("###########");
		if ((c = ft_strchr(buf, '\n')))
		{
			if (c + 1)
			{
				*line = ft_strncat(*line, buf, c + 1 - buf);
							//ft_putendl("HARD");
				!lst->str[0] ? : ft_strdel(&lst->str);
				//			ft_putnbrendl(lst->str[0]);
				lst->str = ft_strnew(0);
				lst->str = ft_strjoin(lst->str, c + 1);
					//ft_putstr("line1 = ");
					//ft_putendl(*line);
					//ft_putendl("--------------");
					//ft_putendl("lst->str1 = ");
					//ft_putendl(lst->str);
					//ft_putendl("--------------");
			}
			return (1);
		}
		else
		{
			c = ft_strjoin(*line, buf);
			!line ? : ft_strdel(line);
			if (*c)
				*line = c;
					//ft_putstr("line2 = ");
					//ft_putendl(*line);
					//ft_putendl("===============");
					//ft_putendl("lst->str2 = ");
					//ft_putendl(lst->str);
					//ft_putendl("================");
		}
	}
	return (0);
}

/*
** Allocate and fill the str
*/

int		fillstr(t_lst *lst, char **line)
{
					//ft_putendl("fillstr");
	//int		ret;
	//char	buf[BUFF_SIZE + 1];
	char	*c;

	if ((c = ft_strchr(lst->str, '\n')))	
	{
		if (c + 1)
		{
					//ft_putendl(*line);
			!line ? : ft_strdel(line);
			*line = ft_strnew(0);
			*line = ft_strncat(*line, lst->str, c + 1 - lst->str);
			!lst->str[0] ? : ft_strdel(&lst->str);
					//ft_putendl("yooaa");
			lst->str = ft_strdup(c + 1);
		}
					//ft_putendl("lst->str -1 = ");
					//ft_putendl(lst->str );
					//ft_putendl("--------------");
					//ft_putnbrendl(ft_strlen(lst->str));
		return (1);
	}
					//ft_putendl("lst->str0 = ");
					//ft_putendl(lst->str);
					//ft_putendl("--------------");
	if (lst->str[0])
	{
		ft_strdel(line);
					////ft_putendl(*line);
		*line = ft_strnew(0);
		//*line = ft_strdup(lst->str);
		*line = ft_strncat(*line, lst->str, ft_strlen(lst->str));
					//ft_putendl("FAIL");
					//ft_putnbrendl(lst->str[0]);
		ft_strdel(&lst->str);
		lst->str = ft_strnew(0);
	}
	if (rd(lst, line))
		return (1);
	// while ((ret = read(lst->fd, buf, BUFF_SIZE)))
	// {
	// 	buf[ret] = '\0';
	// 				//ft_putstr("BUF = ");
	// 				//ft_putendl(buf);
	// 				//ft_putendl("###########");
	// 	if ((c = ft_strchr(buf, '\n')))
	// 	{
	// 		if (c + 1)
	// 		{
	// 			*line = ft_strncat(*line, buf, c + 1 - buf);
	// 						//ft_putendl("HARD");
	// 			ft_strdel(&lst->str);
	// 			lst->str = ft_strnew(0);
	// 			lst->str = ft_strjoin(lst->str, c + 1);
	// 				//ft_putstr("line1 = ");
	// 				//ft_putendl(*line);
	// 				//ft_putendl("--------------");
	// 				//ft_putendl("lst->str1 = ");
	// 				//ft_putendl(lst->str);
	// 				//ft_putendl("--------------");
	// 		}
	// 		return (1);
	// 	}
	// 	else
	// 	{
	// 		c = ft_strjoin(*line, buf);
	// 		!line ? : ft_strdel(line);
	// 		if (*c)
	// 			*line = c;
	// 				//ft_putstr("line2 = ");
	// 				//ft_putendl(*line);
	// 				//ft_putendl("===============");
	// 				//ft_putendl("lst->str2 = ");
	// 				//ft_putendl(lst->str);
	// 				//ft_putendl("================");
	// 	}
	// }
	return (0);
}

/*
** Return the block corresponding to the fd. 
** If fd haven't been seen before, create a block.
*/

t_lst 	*crema(int fd, t_lst *lst)
{
			//ft_putendl("crema");
							//ft_putstr("fd = ");
							//ft_putnbrendl(fd);
	if (lst)
	{
		while (lst)
		{
								//ft_putendl("DEBUG");
								//ft_putnbrendl(lst->fd);
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
							//ft_putstr("lst -> fd2 = ");
							//ft_putnbrendl(lst->fd);		
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
					//ft_putstr("firstm->fd = ");
					//ft_putnbrendl(firstm->fd);

				//ft_putstr("lst->fd1 = ");
				//ft_putnbrendl(lst->fd);
	ok = fillstr(lst, line);
	if (*line[0] == '\n')
		*line[0] = '\0';
	//ft_putendl("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@resultat : ");
	 ft_putstr(*line);
	return (ok);
}
/*
int		get_next_line(const int fd, char **line)
{
			////ft_putendl("get_next_line");
	static t_lst	*firstm;
	t_lst 			*lst;
	int				ok;

	if (!firstm)
		firstm = crema(fd, firstm);
	else
	{
		lst = firstm;
		lst = crema(fd, lst);
	}

	ok = fillstr(lst, line);
	if (*line[0] == '\n')
		*line[0] = '\0';
	// //ft_putstr_fd(*line, 1);
	return (ok);
}
*/
int main (int ac, char **av)
{
	int		fd;
	//int		fd2;
	char	*line;
	int ok;

	(void)ac;
	line = ft_strnew(1);
	fd = open(av[1], O_RDONLY);
			ft_putnbrendl(fd);
	//fd2 = open(av[2], O_RDONLY);
	while((ok = get_next_line(fd, &line)))
		;//ft_putnbrendl(ok);
	//get_next_line(fd2, &line);
	close(fd);
	//close(fd2);
	//fd = open(av[1], O_RDONLY);
	//fd2 = open(av[2], O_RDONLY);
	//ft_putendl("===========================================");
	//while(get_next_line(fd, &line))
	//	;
	//ft_putendl("===========================================");
	//while(get_next_line(fd2, &line))
	//	;
	//close(fd);
	//close(fd2);
	return (0);
}
