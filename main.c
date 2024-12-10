/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrick <rodrick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:10:37 by rodrick           #+#    #+#             */
/*   Updated: 2024/12/10 21:25:44 by rodrick          ###   ########.fr       */
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
    cube->map = (char **)malloc(sizeof(char *) * height);
    if (!cube->map)
        return;
    fd = open(cube->name, O_RDONLY);
    if (fd < 0)
        return;

    height = 0;
    while ((line = get_next_line(fd)))
    {
        cube->map[height] = line;
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
        cube->map[i] = get_next_line(fd);
        i++;
    }
    close(fd);
}

void data_init(t_cube3D *cube, char **av)
{
    cube->name = av[1];
    caculate_map(cube);
    fill_the_map(cube);
    
}

int main(int ac, char **av)
{
    int i;
    
    if (ac != 2)
        return (0);
    t_cube3D *cube;
    data_init(cube, av);
    
}
