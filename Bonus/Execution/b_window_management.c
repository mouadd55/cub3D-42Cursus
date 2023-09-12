/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_window_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:19:21 by moudrib           #+#    #+#             */
/*   Updated: 2023/09/12 14:12:27 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	get_window_resolution(t_vars *vars)
{
	int	i;

	i = -1;
	vars->width = 0;
	vars->height = 0;
	while (vars->map[vars->height])
	{
		if ((int)ft_strlen(vars->map[vars->height]) > vars->width)
			vars->width = ft_strlen(vars->map[vars->height]);
		vars->height++;
	}
	vars->lengths = malloc ((vars->height + 1) * sizeof(int));
	if (!vars->lengths)
		exit(1);
	while (++i < vars->height)
		vars->lengths[i] = (int)ft_strlen(vars->map[i]); // free
}

int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free_data(&vars->infos, NULL, vars->map);
	free (vars->lengths);
	free (vars);
	exit(0);
}

void	create_new_image(t_vars *vars)
{
	vars->image.win_img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->image.win_img)
		exit (1);
	vars->image.win_addr = mlx_get_data_addr(vars->image.win_img,
			&vars->image.bits_per_pixel, &vars->image.line_length,
			&vars->image.endian);
	if (!vars->image.win_addr)
		exit (1);
}

void	create_minimap_image(t_vars *vars)
{
	vars->minimap.minimap_img
		= mlx_new_image(vars->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	vars->minimap.minimap_addr = mlx_get_data_addr(vars->minimap.minimap_img,
			&vars->minimap.bits_per_pixel, &vars->minimap.line_length,
			&vars->minimap.endian);
}

void ft_get_pistol_img(t_vars *vars)
{
	int x;
	int y;
	vars->pistol_img[0] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/Reason011694291748.xpm", &x, &y);
	vars->pistol_img[1] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/Reason021694291747.xpm", &x, &y);
	vars->pistol_img[2] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonF011694291755.xpm", &x, &y);
	vars->pistol_img[3] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonF021694291756.xpm", &x, &y);
	vars->pistol_img[4] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonF031694291756.xpm", &x, &y);
	vars->pistol_img[5] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonF041694291757.xpm", &x, &y);
	vars->pistol_img[6] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonF051694291757.xpm", &x, &y);
	//rel
	vars->pistol_img[7] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR011694291758.xpm", &x, &y);
	vars->pistol_img[8] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR021694291758.xpm", &x, &y);
	vars->pistol_img[9] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR031694291759.xpm", &x, &y);
	vars->pistol_img[10] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR041694291759.xpm", &x, &y);
	vars->pistol_img[11] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR051694291760.xpm", &x, &y);
	vars->pistol_img[12] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR061694291760.xpm", &x, &y);
	vars->pistol_img[13] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR071694291761.xpm", &x, &y);
	vars->pistol_img[14] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR081694291762.xpm", &x, &y);
	vars->pistol_img[15] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR091694291762.xpm", &x, &y);
	vars->pistol_img[16] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR111694291764.xpm", &x, &y);
	vars->pistol_img[17] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR131694291765.xpm", &x, &y);
	vars->pistol_img[18] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR151694291766.xpm", &x, &y);
	vars->pistol_img[19] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR171694291767.xpm", &x, &y);
	vars->pistol_img[20] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR191694291768.xpm", &x, &y);
	vars->pistol_img[21] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR211694291770.xpm", &x, &y);
	vars->pistol_img[22] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR311694291774.xpm", &x, &y);
	vars->pistol_img[23] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR321694291775.xpm", &x, &y);
	vars->pistol_img[24] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR331694291775.xpm", &x, &y);
	vars->pistol_img[25] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR341694291776.xpm", &x, &y);
	vars->pistol_img[26] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR351694291776.xpm", &x, &y);
	vars->pistol_img[27] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR361694291777.xpm", &x, &y);
	vars->pistol_img[28] = mlx_xpm_file_to_image(vars->mlx, "./xpm/ak/ReasonR371694291777.xpm", &x, &y);

	
	vars->pistol_img[29] = 0;
	

}

void ft_get_gun_img(t_vars *vars)
{
	int x;
	int y;
	vars->knife_img[0] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/Knife01.xpm", &x, &y);
	vars->knife_img[1] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/Knife02.xpm", &x, &y);
	vars->knife_img[2] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/Knife03.xpm", &x, &y);
	vars->knife_img[3] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/Knife04.xpm", &x, &y);
	vars->knife_img[4] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/Knife05.xpm", &x, &y);
	vars->knife_img[5] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/KnifeF01.xpm", &x, &y);
	vars->knife_img[6] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/KnifeF02.xpm", &x, &y);
	vars->knife_img[7] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/KnifeF03.xpm", &x, &y);
	vars->knife_img[8] = mlx_xpm_file_to_image(vars->mlx, "./xpm/knif/KnifeF04.xpm", &x, &y);
	vars->knife_img[9] = 0;
	ft_get_pistol_img(vars);

}

void	open_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	get_window_resolution(vars);
	vars->mlx_win = mlx_new_window(vars->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3D");
	if (!vars->mlx_win)
		exit(1);
	if (vars->hid_mouse == -1)
		mlx_mouse_move(vars->mlx_win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	ft_texture(vars);
	ft_get_gun_img(vars);
	create_new_image(vars);
	create_minimap_image(vars);
	init_player_infos(vars);
	get_colors_values_from_file(vars);
}
