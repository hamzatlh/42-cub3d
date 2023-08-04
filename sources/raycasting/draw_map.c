/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/04 18:38:31 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, float a)
{
    int color;

    color = r << 24 | g << 16 | b << 8 | (int)a * 255;
    return (color);
}

void	draw_pixels(mlx_image_t **img, int h, int w, int color)
{
	int	i;
	int	j;

	i = h;
	while (i <= h + TILE_SIZE)
	{
		j = w;
		while (j <= w + TILE_SIZE)
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(mlx_image_t **img, float x, float y)
{
	draw_pixels(img, x * TILE_SIZE, y * TILE_SIZE, get_rgba(0, 0, 255, 1));
}

void	draw_map()
{
	int	i;
	int	j;

	i = 0;
	while (g_game->map->map[i])
	{
		j = 0;
		while (g_game->map->map[i][j])
		{
			if (g_game->map->map[i][j] == '1')
				draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE, get_rgba(255, 255, 255, 1));
			else if (g_game->map->map[i][j] == '0' || ft_strchr("NSEW", g_game->map->map[i][j]))
				draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE, get_rgba(0, 0, 0, 1));
			j++;
		}
		i++;
	}
	draw_player(&g_game->img_map, g_game->player.x, g_game->player.y);
    draw_angle_dda(&g_game->img_map);
}

void DDA(mlx_image_t **img, float X0, float Y0, float X1, float Y1)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = g_game->player.x * TILE_SIZE;
    float Y = g_game->player.y * TILE_SIZE;
    for (int i = 0; i <= steps; i++)
    {
        mlx_put_pixel(*img, X, Y, get_rgba(0, 0, 255, 1));
        X += Xinc;
        Y += Yinc;
    }
}

void draw_angle_dda(mlx_image_t **img)
{
    float dx;
    float dy;
    float x = g_game->player.x * TILE_SIZE;
    float y = g_game->player.y * TILE_SIZE;

    dx = x + cos(g_game->player.angle) * TILE_SIZE;
    dy = y - sin(g_game->player.angle) * TILE_SIZE;
    DDA(img, x, y, dx , dy);
}

int put_pixels(void)
{
    g_game->img_map = mlx_new_image(g_game->mlx, g_game->map->width \
        * TILE_SIZE, g_game->map->height * TILE_SIZE);
    g_game->img_player = mlx_new_image(g_game->mlx, TILE_SIZE/2, TILE_SIZE/2);
    if (!g_game->img_map || !g_game->img_player)
        return (1);
    if (mlx_image_to_window(g_game->mlx, g_game->img_map, 0, 0) < 0)
        return (1);
    if (mlx_image_to_window(g_game->mlx, g_game->img_player, 0, 0) < 0)
        return (1);
    return (0);
}

void move_forward(float move_speed)
{
	if (g_game->map->map[(int)(g_game->player.y)]\
		[(int)(g_game->player.x + cos(g_game->player.angle) * move_speed)] != '1')
	{
		g_game->player.x += cos(g_game->player.angle) * move_speed;
		g_game->player.y -= sin(g_game->player.angle) * move_speed;
	}
}

void move_backward(float move_speed)
{
	if (g_game->map->map[(int)(g_game->player.y)]\
		[(int)(g_game->player.x - cos(g_game->player.angle) * move_speed)] != '1')
	{
		g_game->player.x -= cos(g_game->player.angle) * move_speed;
		g_game->player.y += sin(g_game->player.angle) * move_speed;
	}
}

void move_left(float move_speed)
{
	if (g_game->map->map[(int)(g_game->player.y - cos(g_game->player.angle) * move_speed)]\
		[(int)(g_game->player.x)] != '1')
	{
		g_game->player.x -= sin(g_game->player.angle) * move_speed;
		g_game->player.y -= cos(g_game->player.angle) * move_speed;
	}
}

void move_right(float move_speed)
{
	if (g_game->map->map[(int)(g_game->player.y + cos(g_game->player.angle) * move_speed)]\
		[(int)(g_game->player.x)] != '1')
	{
		g_game->player.x += sin(g_game->player.angle) * move_speed;
		g_game->player.y += cos(g_game->player.angle) * move_speed;
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx;
	float move_speed;
	float rot_speed;

	mlx = param;
	move_speed = 0.05;
	rot_speed = 0.05;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_forward(move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_backward(move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left(move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right(move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_game->player.angle += rot_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_game->player.angle -= rot_speed;

	draw_map();
}
