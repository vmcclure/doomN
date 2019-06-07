/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawobj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:14:48 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/05 17:47:16 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initwallobj(t_doom *doom, t_map map, t_wall *wa, size_t c)
{
	wa->p[0] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z - (map.obj[c].width / 2), 1);
	wa->p[1] = setfvector(map.obj[c].pos.x,
	map.sectors[map.obj[c].sector].floor, map.obj[c].pos.z + (map.obj[c].width / 2), 1);
	wa->p[2] = addfvector(wa->p[0], 0, map.sectors[map.obj[c].sector].height, 0);
	wa->p[3] = addfvector(wa->p[1], 0, map.sectors[map.obj[c].sector].height, 0);
	subdrawwall(wa->p, map.obj[c].pos.x, map.obj[c].pos.y, map.obj[c].pos.z);
}
void	swap_float1(float *a, float *b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void	drawobj(t_doom *doom, t_map map)
{
	t_wall		wa;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	t_fvector	dir;
	size_t		c;

	cammat = matcam(&doom->player);
	projec = matprojection(initcam(setivector2d(800, 800)));
	c = -1;
	while (++c < doom->thismap.objcount)
	{
		dir = subfvtofv(doom->player.pos, map.obj[c].pos);
		dir = normfvector(dir);
		initwallobj(doom, doom->thismap, &wa, c);
		multmatrixdrawwall(wa.p, matroty(atan2(dir.z, dir.x)));
		adddrawwall(wa.p, map.obj[c].pos.x, map.obj[c].pos.y, map.obj[c].pos.z);
		multmatrixdrawwall(wa.p, cammat);
		wa.offset[0] = 1;
		wa.offset[1] = 1;
		wa.offset[2] = 1;
		wa.offset[3] = 1;
		if (clip(&doom->player, wa.p, wa.offset, c))
		{
			wallproj(wa.p, projec);
			if (wa.p[0].x > wa.p[1].x)
			{
				ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
				ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
				swap_float1(&wa.offset[1], &wa.offset[0]);
				swap_float1(&wa.offset[3], &wa.offset[2]);
			}
			drow_wall(doom->win->pixels, wa, doom->texture[doom->thismap.obj[c].texture], wa.offset, 0.1);
		}
	}
}