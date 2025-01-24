/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrick <rodrick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:41:51 by rodrick           #+#    #+#             */
/*   Updated: 2025/01/22 16:28:38 by rodrick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int color_assigned(char *str, int *i)
{
    int color = 0;

    while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
    {
        color = color * 10 + (str[*i] - '0');
        (*i)++;
    }
    
    return color;
}

int colors(char *thec, t_cube3D *cube, char c)
{
    int i = 0;

    if (thec[i] == c)
        i += 2;
    if (c == 'C')
    {
        cube->attribut->color->red = color_assigned(thec, &i);
        if (thec[i] == ',') i++;
        cube->attribut->color->green = color_assigned(thec, &i);
        if (thec[i] == ',') i++;
        cube->attribut->color->blue = color_assigned(thec, &i);
    }
    else if (c == 'F')
    {
        cube->attribut->color->f_red = color_assigned(thec, &i);
        if (thec[i] == ',') i++;
        cube->attribut->color->f_green = color_assigned(thec, &i);
        if (thec[i] == ',') i++;
        cube->attribut->color->f_blue = color_assigned(thec, &i);
    }
    return 0;
}




