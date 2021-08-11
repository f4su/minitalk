#include <signal.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putnbr_fd(int n, int fd)
{

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
			ft_putchar_fd('-', fd);
		if (n > 9)
			ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*aux;
	size_t		i;

	i = 0;
	aux = (unsigned char *)b;
	while (i < len)
		aux[i++] = c;
	return (aux);
}

void	ft_interpreter(int sign)
{
	static size_t	i;
	static int	bit;
	static char	buff[100];

	if (--bit == -1)
	{
		bit = 6;
		++i;
	}
	buff[i] &= ~(1 << 7);
	if (sign == SIGUSR1)
		buff[i] |= (1 << bit);
	else if (sign == SIGUSR2)
		buff[i] &= ~(1 << bit);
	if (i == 99 || buff[i] == 127)
	{
		buff[i] = 0;
		write(STDOUT_FILENO, buff, i + 1);
		ft_memset(buff, '\0', 99);
		i = 0;
		bit = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, "usage: ./server\n", 16);
		return (1);
	}
	else
	{
		pid = getpid();
		ft_putnbr_fd(pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		while (42)
		{
			signal(SIGUSR1, ft_interpreter);
			signal(SIGUSR2, ft_interpreter);
		}
	}
}
