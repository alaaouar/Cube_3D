/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:11:32 by rodrick           #+#    #+#             */
/*   Updated: 2025/02/21 19:37:12 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void    my_mlx_pixel_put(t_cube3D *cube, int x, int y, int color)
{
    char    *dst;

    dst = cube->mlx->addr + (y * cube->mlx->line_length + x * (cube->mlx->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_cube(t_cube3D *cube, int start_x, int start_y, int size, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + size)
    {
        x = start_x;
        while (x < start_x + size)
        {
            my_mlx_pixel_put(cube, x, y, color);
            x++;
        }
        y++;
    }
}

void    map_draw(t_cube3D *cube)
{
    int x;
    int y;
    int cube_size = 15;

    cube->mlx->img = mlx_new_image(cube->mlx->mlx, 500, 500);
    cube->mlx->addr = mlx_get_data_addr(cube->mlx->img, &cube->mlx->bits_per_pixel, &cube->mlx->line_length, &cube->mlx->endian);

    x = 8;
    while (cube->file[x] != NULL)
    {
        y = 0;
        while (cube->file[x][y] != '\0')
        {
            if (cube->file[x][y] == '1')
                draw_cube(cube, y * cube_size, x * cube_size, cube_size, 0x00FF0000); // Red for '1'
            else if (cube->file[x][y] == '0')
                draw_cube(cube, y * cube_size, x * cube_size, cube_size, 0x0000FF00); // Green for '0'
            else if (cube->file[x][y] == 'N' ||  cube->file[x][y] == 'E' || cube->file[x][y] == 'W' || cube->file[x][y] == 'S')
                draw_cube(cube, y * cube_size, x * cube_size, cube_size, 0xFFFFFFFF);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(cube->mlx->mlx, cube->mlx->win, cube->mlx->img, 0, 0);
}
