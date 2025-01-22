/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrick <rodrick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:10:37 by rodrick           #+#    #+#             */
/*   Updated: 2025/01/22 16:28:42 by rodrick          ###   ########.fr       */
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
    cube->attribut->no = direction_line(cube->map, "NO", 0);
    cube->attribut->so = direction_line(cube->map, "SO", 0);
    cube->attribut->we = direction_line(cube->map, "WE", 0);
    cube->attribut->ea = direction_line(cube->map, "EA", 0);
    cube->attribut->s = direction_line(cube->map, NULL, 'S');
    cube->attribut->f = direction_line(cube->map, NULL, 'F');
    cube->attribut->c = direction_line(cube->map, NULL, 'C');
}

void    map_attributes(t_cube3D *cube)
{
    get_direction(cube);
}


void map_in_it(t_cube3D *cube, char **av)
{
    cube->name = av[1];
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
}

void    print_map(t_cube3D *cube)
{
    int i = 0;

    while (cube->map[i])
    {
        printf("%s", cube->map[i]);
        i++;
    }
    printf("\n----------------------------------------\n");
    if (cube->attribut->no)
        printf("NO: %s\n", cube->attribut->no);
    if (cube->attribut->so)
        printf("SO: %s\n", cube->attribut->so);
    if (cube->attribut->we)
        printf("WE: %s\n", cube->attribut->we);
    if (cube->attribut->ea)
        printf("EA: %s\n", cube->attribut->ea);
    if (cube->attribut->s)
        printf("S: %s\n", cube->attribut->s);
    if (cube->attribut->f)
        printf("F: %s\n", cube->attribut->f);
    if (cube->attribut->c)
        printf("C: %s\n", cube->attribut->c);
    printf("R= %d, G= %d, B= %d\n", cube->attribut->color->red, cube->attribut->color->green, cube->attribut->color->blue);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (0);
    t_cube3D *cube = (t_cube3D *)malloc(sizeof(t_cube3D));
    if (!cube)
        return (1);
    map_in_it(cube, av);
    print_map(cube);
    // Free allocated memory here if necessary
    return (0);
}
