/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrick <rodrick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:10:37 by rodrick           #+#    #+#             */
/*   Updated: 2024/12/10 20:56:58 by rodrick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3D.h"

void caculate_map(t_cube3D *cube)
{
    int height;
    int fd;
    char *line;
    
    height = 0;
    fd = open("./map.cub", O_RDONLY);
    if (fd < 0)
        return; // Handle error appropriately

    // First pass to count the number of lines
    while ((line = get_next_line(fd)))
    {
        height++;
        free(line); // Free the line after counting
    }
    close(fd);

    // Allocate memory for the map
    cube->map = (char **)malloc(sizeof(char *) * height);
    if (!cube->map)
        return; // Handle memory allocation failure

    // Second pass to fill the map
    fd = open("./map.cub", O_RDONLY);
    if (fd < 0)
        return; // Handle error appropriately

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
    fd = open("./map.cub", O_RDONLY);
    if (fd < 0)
        return; // Handle error appropriately

    while (i < cube->height)
    {
        cube->map[i] = get_next_line(fd);
        i++;
    }
    close(fd);
}

void data_init(t_cube3D *cube)
{
    caculate_map(cube);
    fill_the_map(cube);
}

int main(int ac, char **av)
{
    int i;
    
    t_cube3D *cube;
    data_init(cube);
    printf("cube->height = %d\n", cube->height);
    i = 0;
    while (cube->map[i])
    {
        printf("%s\n", cube->map[i]);
        i++;
    }
    
}
