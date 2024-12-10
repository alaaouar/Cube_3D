#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1337
#endif

typedef struct s_cube3D
{
    int width;
    int height;
    char **map;
}               t_cube3D;


size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
void	*ft_free(char *line);

#endif