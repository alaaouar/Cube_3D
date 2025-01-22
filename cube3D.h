#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1337
#endif

typedef struct s_color
{
    int red;
    int green;
    int blue;
}               t_color;


typedef struct attribut
{
    char *no;
    char *so;
    char *we;
    char *ea;
    char *s;
    char *f;
    char *c;
    t_color *color;
}               t_attribut;

typedef struct s_cube3D
{
    int width;
    int height;
    char **map;
    char *name;
    t_attribut *attribut;
}               t_cube3D;


size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
void	*ft_free(char *line);
int	colors(char *thec, t_cube3D *cube, char c);
void caculate_map(t_cube3D *cube);
void fill_the_map(t_cube3D *cube);
void    map_attributes(t_cube3D *cube);

#endif