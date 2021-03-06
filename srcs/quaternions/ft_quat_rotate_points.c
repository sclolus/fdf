/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_rotate_points.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 09:21:26 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/17 02:55:03 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

inline static void			ft_set_rot_quats(t_vec *axis
	, t_quat *rotation_quat, t_quat *rotation_quat_prime, double angle)
{
	*rotation_quat = (t_quat){axis->x * sin(angle / 2), axis->y * sin(angle / 2)
						, axis->z * sin(angle / 2), cos(angle / 2)};
	*rotation_quat_prime = ft_get_conjugate_quat(rotation_quat);
}

inline static void			ft_update_line_data(t_mem_block *data, uint64_t i)
{
	((t_line*)data->block + i)->dx = ((t_line*)data->block + i)->start.x
			- ((t_line*)data->block + i)->end.x;
	((t_line*)data->block + i)->dy = ((t_line*)data->block + i)->start.y
			- ((t_line*)data->block + i)->end.y;
	((t_line*)data->block + i)->e = ((t_line*)data->block + i)->dy
			/ ((t_line*)data->block + i)->dx;
}

void						ft_quat_rotate_points(t_vec *axis, double angle
										, t_mem_block *data)
{
	t_quat		rotation_quat;
	t_quat		rotation_quat_prime;
	t_quat		view_quat;
	t_quat		tmp_quat;
	uint64_t	i;

	i = 0;
	ft_set_rot_quats(axis, &rotation_quat, &rotation_quat_prime, angle);
	while ((i) * sizeof(t_line) < data->offset)
	{
		ft_memcpy(&view_quat, &((t_line*)data->block + i)->start
				, sizeof(t_vec));
		view_quat.w = 0;
		tmp_quat = ft_multiply_quat(ft_multiply_quat(
					rotation_quat, view_quat), rotation_quat_prime);
		ft_memcpy(&((t_line*)data->block + i)->start, &tmp_quat, sizeof(t_vec));
		ft_memcpy(&view_quat, &((t_line*)data->block + i)->end, sizeof(t_vec));
		view_quat.w = 0;
		tmp_quat = ft_multiply_quat(ft_multiply_quat(
					rotation_quat, view_quat), rotation_quat_prime);
		ft_memcpy(&((t_line*)data->block + i)->end, &tmp_quat, sizeof(t_vec));
		ft_update_line_data(data, i);
		if ((++i) * sizeof(t_line) >= data->offset && data->next && !(i = 0))
			data = data->next;
	}
}
