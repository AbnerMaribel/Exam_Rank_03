/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaribel <amaribel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:49:45 by amaribel          #+#    #+#             */
/*   Updated: 2022/04/07 12:02:46 by amaribel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

void	ft_putnbr(int	n, int	*counter)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*counter) += 11;
	}
	else
	{
		if (n < 0)
		{
			n = (-1) * n;
			write(1, "-", 1);
			(*counter)++;
		}
		if (n <= 9)
		{
			n = n + '0';
			write(1, &n, 1);
			(*counter)++;
		}
		else
		{
			ft_putnbr((n / 10), counter);
			ft_putnbr((n % 10), counter);
		}
	}
}


void	ft_putstr(char	*s, int	*counter)
{
	if (!s)
	{
		write(1, "(null)", 6);
		(*counter) += 6;
		return ;
	}
	while (*s)
	{
		write(1, s++, 1);
		(*counter)++;
	}
}

void	put_hex(unsigned int	c, int	*counter)
{
	if (c <= 9)
	{
		c = c + 48;
		write(1, &c, 1);
		(*counter)++;
	}
	else if (c > 9 && c <= 15)
	{
		c = c + 87;
		write(1, &c, 1);
		(*counter)++;
	}
	else
	{
		put_hex((c / 16), counter);
		put_hex((c % 16), counter);
	}
}


void	conversion(char *s, va_list ap, int *counter)
{
	if (*s == 'd')
		ft_putnbr((va_arg(ap, int)), counter);
	else if (*s == 's')
		ft_putstr((va_arg(ap, char *)), counter);
	else if (*s == 'x')
		put_hex((va_arg(ap, unsigned int)), counter);
	else if (*s == '%')
	{
		write(1, s, 1);
		(*counter)++;
	}
}

int	ft_printf(const char	*s, ...)
{
	int		counter;
	va_list	ap;

	va_start(ap, s);
	counter = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s && *s != '%')
		{
			write(1, s, 1);
			counter++;
		}
		if (*s == '%')
		{
			s++;
			conversion((char *)s, ap, &counter);
		}
		s++;
	}
	va_end(ap);
	return (counter);
}

int main()
{
	int a = 45;
	char *s = "asd";
	ft_printf("www %d %s %x\n", a, s, a);
}
