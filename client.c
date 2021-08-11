#include <unistd.h>
#include <signal.h>

static int	ft_send_ascii(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (--bit > -1)
	{
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
	}
	return (0);
}

static int	ft_message(pid_t num_pid, char *b)
{
	int	i;

	i = 0;
	while (b[i] >= ' ' && b[i] <= '~')
	{
		if (ft_send_ascii(num_pid, b[i]))
			return (1);
		++i;
	}
	i = 0;
	while (i < 7)
	{
		kill(num_pid, SIGUSR1);
		usleep(1000);
		i++;
	}
	return (0);

}

static int	ft_atoi(const char *str)
{
	long	i;
	long	j;
	char	neg;

	i = 0;
	j = 0;
	neg = '+';
	while((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i]== '-')
		neg = str[i++];
	if (str[i] == '+' && neg == '-')
		return (0);
	i += (str[i] == '+');
	while (str[i] >= '0' && str[i]<= '9')
	{
		j *= 10;
		j += str[i] - '0';
		i++;
	}
	if (j < 0)
		return ((neg != '-') * -1);
	if (neg == '-')
		j *= -1;
	return ((int)j);
}

int	main(int argc, char **argv)
{
	int	num_pid;

	if (argc < 3)
	{
		write(2, "Introduzca un PID y una cadena\n", 32);
		return (1);
	}
	if ((num_pid = ft_atoi(argv[1])) == 0)
	{
		write(2, "PID desconocido\n", 32);
		return (1);
	}
	ft_message(num_pid, argv[2]);
	return (0);
}
