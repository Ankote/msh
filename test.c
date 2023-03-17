#include "minishell.h"
#include <string.h>

int main()
{
	char *buffer;
	int fd;

	buffer = "stop";
	if(!strcmp(buffer, "stop"))
		printf("ok");
	fd = open("tnp", O_CREAT, O_RDWR, 0777);
	while(1)
	{
		buffer = get_next_line(0);
		if(!buffer || !strcmp(buffer, "stop\n"))
			return(0);
		ft_putendl_fd(buffer, fd);
	}
}
