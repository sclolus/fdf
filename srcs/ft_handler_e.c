/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 07:48:26 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/17 03:56:09 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_handler_e(void *param)
{
	ft_quat_rotate_points(&(t_vec){0, 0, 1}, -ROTATION_SPEED * PI / 180
						, (t_mem_block*)((t_mem_block**)param)[3]);
	ft_draw_lines(((t_mlx_ptr)((char**)param)[0]), (t_mlx_ptr)((char**)param)[1]
				, (t_mlx_img)((char**)param)[2]
				, (t_mem_block*)((t_mem_block**)param)[3]);
}
