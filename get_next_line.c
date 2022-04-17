/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaribel <amaribel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:24:33 by amaribel          #+#    #+#             */
/*   Updated: 2022/04/07 12:27:30 by amaribel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

int	ft_strlen(char *s)
{
	if (!s)
		return (0);
	int	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, char *src, int size)
{	
	int	i = 0;
	if (size == 0)
		return (dst);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i = 0;
	int		j = 0;
	int		z = 0;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == 0)
	{
		free (s1);
		return (0);
	}
	while (s1 && s1[i])
		dest[z++] = s1[i++];
	while (s2[j])
		dest[z++] = s2[j++];
	dest[z] = '\0';
	free (s1);
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		else
			i++;
	}
	return 0;
}

void	change_buf_line(char	*buf, char	**line)
{
	char	*n;

	n = ft_strchr(buf, '\n');
	*n = '\0';
	*line = ft_strjoin(*line, buf);
	*line = ft_strjoin(*line, "\n");
	n++;
	ft_strncpy(buf, n, ft_strlen(n) + 1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	long		count;

	if ((read(fd, 0, 0) == -1)|| BUFFER_SIZE < 0)
		return (0);
	line = 0;
	count = 1;
	while ((ft_strchr(buf, '\n') == 0) && count > 0)
	{
		line = ft_strjoin(line, buf);
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0 || (count == 0 && line[0] == '\0'))
		{
			free (line);
			return (0);
		}
		buf[count] = '\0';
	}
	if (ft_strchr(buf, '\n'))
		change_buf_line(buf, &line);
	return (line);
}

int main()
{
	int fd; 
	if((fd = open("text.txt", O_RDONLY)) == -1)
		printf("Cant open\n");
	char *line;
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}
