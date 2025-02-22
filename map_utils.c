/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:04:46 by alaaouar          #+#    #+#             */
/*   Updated: 2025/02/22 19:08:13 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

char *ft_strdup(char *str)
{
    char *new_str;
    int i = 0;

    new_str = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!new_str)
        return (NULL);
    while (str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}


int calcule_maps(char **str)
{
    int i = 0;
    int map_lines = 0;

    while (str[i])
    {
        if (str[i][0] == '1' || str[i][0] == '0')
        {
            map_lines++;
        }
        i++;
    }
    return map_lines;
}

void get_the_map_only(t_cube3D *cube)
{
    int i = 0;
    int j = 0;
    int map_started = 0;
    
    cube->attribut->map = (char **)malloc(sizeof(char *) * calcule_maps(cube->file));

    while (cube->file[i]) {
        if (cube->file[i][j] == '\0' || cube->file[i][j] == '\n' || cube->file[i][j] == '\t') {
            i++;
            continue;
        }
        if (cube->file[i][j] == '1' || cube->file[i][j] == '0') {
            map_started = 1;
        }
        if (map_started) {
            cube->attribut->map[i] = ft_strdup(cube->file[i]);
            printf("%s", cube->attribut->map[i]);
            i++;
        } else {
            i++;
        }
    }
}

