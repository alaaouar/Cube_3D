#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mlx_linux/mlx.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_ray {
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
} t_ray;

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void put_pixel(t_data *data, int x, int y, int color) {
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void renderScene(t_data *data, t_ray *ray) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = ray->dirX + ray->planeX * cameraX;
        double rayDirY = ray->dirY + ray->planeY * cameraX;
        
        int mapX = (int)ray->posX;
        int mapY = (int)ray->posY;
        
        double sideDistX;
        double sideDistY;
        
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        
        int stepX;
        int stepY;
        int hit = 0;
        int side;
        
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (ray->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - ray->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (ray->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - ray->posY) * deltaDistY;
        }
        
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        
        if (side == 0) perpWallDist = (mapX - ray->posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - ray->posY + (1 - stepY) / 2) / rayDirY;
        
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        
        int color = 0xFFFFFF;
        if (side == 1) color /= 2;
        for (int y = drawStart; y < drawEnd; y++) {
            put_pixel(data, x, y, color);
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int main() {
    t_data data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster");
    data.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    t_ray ray = {12, 12, -1, 0, 0, 0.66};
    
    renderScene(&data, &ray);
    mlx_loop(data.mlx);
    
    return 0;
}
