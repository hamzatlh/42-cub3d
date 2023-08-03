/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/03 21:45:25 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, float a)
{
    int color;

    color = r << 24 | g << 16 | b << 8 | (int)a * 255;
    return (color);
}

void draw_sqr(mlx_image_t **img, int i, int j)
{
    int tmp_x, tmp_y;

    tmp_x = i * TILE_SIZE;
    while (tmp_x < i * TILE_SIZE + TILE_SIZE - 1)
    {
        tmp_y = j * TILE_SIZE;
        while (tmp_y < j * TILE_SIZE + TILE_SIZE - 1)
        {
            if(g_game->map->map[i][j] == '1')
                    mlx_put_pixel(*img, tmp_x, tmp_y ,  get_rgba(255, 150, 0, 2));

            tmp_y++;
            mlx_put_pixel(*img, tmp_x, tmp_y , 0xffffffff);
        }
        tmp_x++;
        mlx_put_pixel(*img, tmp_x, tmp_y , get_rgba(0, 255, 0, 1));
    }
}

void draw_player(mlx_image_t **img, int i, int j)
{
    int tmp_x, tmp_y;

    tmp_x = i * TILE_SIZE;
    while (tmp_x < i * TILE_SIZE + TILE_SIZE - 50)
    {
        tmp_y = j * TILE_SIZE;
    while (tmp_y < j * TILE_SIZE + TILE_SIZE - 50)
    {
        mlx_put_pixel(*img, tmp_x, tmp_y , get_rgba(0, 0, 255, 1));
        tmp_y++;
    }
        tmp_x++;
    }
}

void put_elements(mlx_image_t **img)
{
    // (void)img;
	int j = 0;
	int i = -1;
    int tmp_x;
    int tmp_y;
	
    tmp_x = i * TILE_SIZE;
    tmp_y = j * TILE_SIZE;
    while (++i < 10)
    {
        j = 0;
        while (j < 10)
        {
            draw_sqr(img, i, j);
            j++;
        }
    }
    // draw_player(img, g_game->player.x, g_game->player.y);
    // DDA(img, g_game->player.x * TILE_SIZE, g_game->player.y * TILE_SIZE, (g_game->player.x + 5) * TILE_SIZE, (g_game->player.y + 5) * TILE_SIZE);
}

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		g_game->img->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		g_game->img->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		g_game->img->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		g_game->img->instances[0].x += 5;
// }


void DDA(mlx_image_t **img, int X0, int Y0, int X1, int Y1)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        mlx_put_pixel(*img, X, Y , get_rgba(0, 0, 255, 1));
        X += Xinc;
        Y += Yinc;
    }
}

int draw_pixel(void)
{
    mlx_image_t *img;
    img = mlx_new_image(g_game->mlx, 1280, 720);
    if (!img)
        return (1);
    if (mlx_image_to_window(g_game->mlx, img, 0, 0) < 0)
        return (1);
    put_elements(&img);
    // mlx_loop_hook(g_game->mlx, ft_hook, g_game->mlx);
    mlx_loop(g_game->mlx);
    return (0);
}
