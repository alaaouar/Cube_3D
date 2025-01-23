/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrick <rodrick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:17:15 by elel-yak          #+#    #+#             */
/*   Updated: 2025/01/23 20:45:50 by rodrick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

size_t	ft_strlen(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
		count++;
	return (count);
}
 
void	*ft_free(char *line)
{
	free (line);
	return (NULL);
}
