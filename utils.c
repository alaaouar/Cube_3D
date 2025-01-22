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

int	ft_isdigit(int c)
{
	return (c <= 57 && c >= 48);
}
int    color_assigned(char *str, int i)
{
    int color;
    
    color = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            color = color * 10 + str[i] - '0';
        else
            break;
        i++;
    }
    return (color);
}

int	colors(char *thec, t_cube3D *cube, char c)
{
    int i;
    
    i = 0;
    if (thec[i] == c)
        i += 2;
    cube->attribut->color->red = color_assigned(thec, i);
    if (thec[i] == ',')
        i++;
    cube->attribut->color->green = color_assigned(thec, i);
    if (thec[i] == ',')
        i++;
    cube->attribut->color->blue = color_assigned(thec, i);
    return (1);
}




