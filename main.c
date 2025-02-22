/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:10:37 by rodrick           #+#    #+#             */
/*   Updated: 2025/02/22 19:09:47 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3D.h"

void caculate_map(t_cube3D *cube)
{
    int height;
    int fd;
    char *line;
    
    height = 0;
    fd = open(cube->name, O_RDONLY);
    if (fd < 0)
        return;
    while ((line = get_next_line(fd)))
    {
        height++;
        free(line);
    }
    close(fd);
    cube->file = (char **)malloc(sizeof(char *) * height);
    if (!cube->file)
        return;
    fd = open(cube->name, O_RDONLY);
    if (fd < 0)
        return;

    height = 0;
    while ((line = get_next_line(fd)))
    {
        cube->file[height] = line;
        height++;
    }
    cube->height = height;
    close(fd);
}

void fill_the_map(t_cube3D *cube)
{
    int i;
    int fd;

    i = 0;
    fd = open(cube->name, O_RDONLY);
    if (fd < 0)
        return;
    while (i < cube->height)
    {
        cube->file[i] = get_next_line(fd);
        i++;
    }
    close(fd);
}

char  *direction_line(char **map, char *type , char c)
{
    int i;

    i = 0;
    if (type)
    {
        while (map[i])
        {
            if (map[i][0] == type[0] && map[i][1] == type[1])
                return (map[i]);
            i++;
        }
    }
    else if (c)
    {
        while (map[i])
        {
            if (map[i][0] == c)
                return (map[i]);
            i++;
        }
    }
    return (NULL);
}
void    get_direction(t_cube3D *cube)
{
    cube->attribut->no = direction_line(cube->file, "NO", 0);
    cube->attribut->so = direction_line(cube->file, "SO", 0);
    cube->attribut->we = direction_line(cube->file, "WE", 0);
    cube->attribut->ea = direction_line(cube->file, "EA", 0);
    cube->attribut->s = direction_line(cube->file, NULL, 'S');
    cube->attribut->f = direction_line(cube->file, NULL, 'F');
    cube->attribut->c = direction_line(cube->file, NULL, 'C');
}

void    map_attributes(t_cube3D *cube)
{
    get_direction(cube);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}
void    map_cub(char *str)
{
    int i;
    int j;
    char *cub;

    cub = ".cub";
    i = 0;
    while (str[i] != '\0')
        i++;
    j = 3;
    if (i < 4)
    {
        ft_putstr_fd("map name not valid \n", 2);
        exit(1);
    }
    while (j >= 0)
    {
        if (str[i - 1] != cub[j])
        {
            ft_putstr_fd("map name not valid \n", 2);
            exit(1);
        }
        i--;
        j--;
    }
}

void map_in_it(t_cube3D *cube, char **av)
{
    cube->name = av[1];
    map_cub(av[1]);
    cube->attribut = (t_attribut *)malloc(sizeof(t_attribut));
    if (!cube->attribut)
        return;
    cube->attribut->color = (t_color *)malloc(sizeof(t_color));
    if (!cube->attribut->color)
        return;
    caculate_map(cube);
    fill_the_map(cube);
    map_attributes(cube);
    colors(cube->attribut->c, cube, 'C');
    colors(cube->attribut->f, cube, 'F');
}
void	handle_exit(int keycode, t_cube3D *cube)
{
	if (keycode == 65307)
	{
		ft_putstr_fd("exiting... \n", 1);
        exit(0);
	}
}
int	handle_keyboard(int keycode, t_cube3D *cube)
{
    handle_exit(keycode, cube);
    return (0);
}

void    print_map(t_cube3D *cube)
{
    int i = 0;
    while (cube->attribut->map[i])
    {
        printf("here %s\n", cube->attribut->map[i]);
        i++;
    }
}

double get_player_pos(char **map, char c)
{
    int i;
    int j;

    j = 0;
    i = 0;
    if (c == 'X')
    {
        while (map[i])
        {
            j = 0;
            while (map[i][j])
            {
                if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
                    return (i);
                j++;
            }
            i++;
        }
    }
    i = 0;
    if (c == 'Y')
    {
        while (map[i])
        {
            j = 0;
            while (map[i][j])
            {
                if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
                    return (j);
                j++;
            }
            i++;
        }
    }
    return (0);
}
void    rey_cast(t_cube3D *cube)
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    int i = 0; 
    
    while (cube->attribut->map[i])
    {
        printf("here %s\n", cube->attribut->map[i]);
        i++;
    }
    posX = get_player_pos(cube->attribut->map, 'X');
    posY = get_player_pos(cube->attribut->map, 'Y');
    
    printf("posX = %f\n", posX);
    printf("posY = %f\n", posY);
}


int ft_mlx_init(t_cube3D *cube)
{
    cube->mlx = malloc(sizeof(t_mlx));
    cube->mlx->mlx = mlx_init();
    if (!cube->mlx->mlx)
        return (1);
    cube->mlx->win = mlx_new_window(cube->mlx->mlx, 500, 500, "my cube 3D");
    get_the_map_only(cube);
    rey_cast(cube);
    map_draw(cube);
    mlx_key_hook(cube->mlx->win, handle_keyboard, &cube);
    mlx_loop(cube->mlx->mlx);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (0);
    t_cube3D *cube = (t_cube3D *)malloc(sizeof(t_cube3D));
    if (!cube)
        return (1);
    map_in_it(cube, av);
    ft_mlx_init(cube);
    print_map(cube);
    return (0);
}
