/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/02 20:01:35 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	parser(char *file)
{
	t_map	map;

	printf("Parsing file %s\n", file);
	get_map(file);
	map.width = 1280;
	map.height = 720;
	return (map);
}
