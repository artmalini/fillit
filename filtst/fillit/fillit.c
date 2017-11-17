#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	**buff;

	i = 0;
	fd = 0;
	if (argc > 1)
	{
		while (argv[1])
		{
			fd = open(argv[i], O_RDONLY);
			buff = malloc(BUFFER_SIZE);
			num = parse_file(fd, buff);
			i++;			
		}
	}
	ft_putstr("xDD");

	return (0);
}
