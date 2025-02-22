#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "mlx_linux/mlx.h"


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1337
#endif

typedef struct s_color
{
    int red;
    int green;
    int blue;
    int f_red;
    int f_green;
    int f_blue;
}               t_color;


typedef struct attribut
{
    char **map;
    char *no;
    char *so;
    char *we;
    char *ea;
    char *s;
    char *f;
    char *c;
    t_color *color;
}               t_attribut;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *img;
    void *addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
}               t_mlx;


typedef struct s_cube3D
{
    int width;
    int height;
    char **file;
    char *name;
    t_attribut *attribut;
    t_mlx *mlx;
}               t_cube3D;

void    map_draw(t_cube3D *cube);
size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
void	*ft_free(char *line);
int     colors(char *thec, t_cube3D *cube, char c);
void    caculate_map(t_cube3D *cube);
void    fill_the_map(t_cube3D *cube);
void    map_attributes(t_cube3D *cube);
void get_the_map_only(t_cube3D *cube);

#endif