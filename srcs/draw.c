/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/07 19:36:37 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fvector	inspectplane(t_fvector planep, t_fvector planen,
t_fvector linestart, t_fvector lineend)
{
	t_fvector	linestarttoend;
	t_fvector	linetoinspector;
	t_fvector	planedadbd;
	float t;

	planen = normfvector(planen);
	planedadbd.x = -dotproductfvtofv(planen, planep);
	planedadbd.y = dotproductfvtofv(linestart, planen);
	planedadbd.z = dotproductfvtofv(lineend, planen);
	t = (-planedadbd.x - planedadbd.y) /
	(planedadbd.z - planedadbd.y);
	linestarttoend = subfvtofv(lineend, linestart);
	linetoinspector = multfvector(linestarttoend, t, t, t);
	return (addfvtofv(linestart, linetoinspector));
}

int		crossline(t_line line, t_fvector2d *ret)
{
	float dx1;
	float dy1;
	float dx2;
	float dy2;

	dx1 = line.p[1].x - line.p[0].x;
	dy1 = line.p[1].y - line.p[0].y;
	dx2 = line.p[3].x - line.p[2].x;
	dy2 = line.p[3].y - line.p[2].y;
	ret->x = dy1 * dx2 - dy2 * dx1;
	if (!ret->x || !dx2)
		return (0);
	ret->y = line.p[2].x * line.p[3].y - line.p[2].y * line.p[3].x;
	ret->x = ((line.p[0].x * line.p[1].y - line.p[0].y
	* line.p[1].x) * dx2 - ret->y * dx1) / ret->x;
	ret->y = (dy2 * ret->x - ret->y) / dx2;
	return (((line.p[0].x <= ret->x && line.p[1].x >= ret->x) ||
	(line.p[1].x <= ret->x && line.p[0].x >= ret->x))
	&& ((line.p[2].x <= ret->x && line.p[3].x >= ret->x)
	|| (line.p[3].x <= ret->x && line.p[2].x >= ret->x)));
}

int		switchcordwall(t_fvector *p1, t_fvector *p2, float *offset,
t_fvector2d angle)
{
	float		t1;
	float		t2;
	t_fvector2d ret;
	t_fvector	tmpp;
	t_line l;

	t1 = sqrt((fabsf(p2->x - p1->x) * fabsf(p2->x - p1->x)) +
	(fabsf(p2->z - p1->z) * fabsf(p2->z - p1->z)));
	l = setline(setfvector2d(p1->x, p1->z), setfvector2d(p2->x, p2->z),
	setfvector2d(0, 0), setfvector2d(angle.x * 100.0, angle.y * 100.0));
	crossline(l, &ret);
	tmpp = *p1;
	p1->x = ret.x;
	p1->z = ret.y;
	// if (p1->z > p2->z)
	// 		return (0);
	t2 = sqrt((fabsf(p2->x - p1->x) * fabsf(p2->x - p1->x))
	+ (fabsf(p2->z - p1->z) * fabsf(p2->z - p1->z)));
	*offset = t2/t1;
	p1->y = flerp(tmpp.y, p2->y, 1.0 - (*offset));
	p1->w = flerp(tmpp.w, p2->w, 1.0 - (*offset));
	return (1);
}

int		clip(t_player *player, t_fvector p[4], float offset[4], size_t c)
{
	int per;
	int per1;
	t_fvector2d ret;
	t_fvector	 tmpp[4];
	t_line l;
	float pos;
	float pos1;
	float pos2;
	int peresechenie;
	peresechenie = 1;
	if (p[0].z <= 0 && p[1].z <= 0 && p[2].z <= 0 && p[3].z <= 0)
		return (0);

	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(-1.0471975512/2.0) * 1000;
	l.p[1].y = sin(-1.0471975512/2.0) * 1000;
	l.p[2].x = p[0].z;
	l.p[2].y = p[0].x;
	l.p[3].x = p[1].z;
	l.p[3].y = p[1].x;
	tmpp[0] = p[0];
	tmpp[1] = p[1];
	tmpp[2] = p[2];
	tmpp[3] = p[3];
	peresechenie = collideline(l);
	per = 0;
	// if (c == 5)
	// {
	// 	printf ("tyt\n");
	// }
	if (peresechenie == 1)					// лево низ
	{		
		per = 1;
		switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
		cos(-1.0471975512) * 1000, sin(-1.0471975512) * 1000));
	}
	l.p[2].x = p[2].z;
	l.p[2].y = p[2].x;
	l.p[3].x = p[3].z;
	l.p[3].y = p[3].x;
	peresechenie = collideline(l);
	if (peresechenie == 1)					// лево верх
	{
	
		switchcordwall(&p[3], &p[2], &offset[3], setfvector2d(
		cos(-1.0471975512) * 1000, sin(-1.0471975512) * 1000));
	}
	l.p[1].x = cos(1.0471975512) * 1000;
	l.p[1].y = sin(1.0471975512) * 1000;
	l.p[2].x = tmpp[0].x;
	l.p[2].y = tmpp[0].z;
	l.p[3].x = tmpp[1].x;
	l.p[3].y = tmpp[1].z;
	peresechenie = collideline(l);
	if (peresechenie == 1)					// право низ
	{
	 	switchcordwall(&tmpp[0], &tmpp[1], &offset[0], setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
		p[0] = tmpp[0];
	}
	l.p[2].x = tmpp[2].x;
	l.p[2].y = tmpp[2].z;
	l.p[3].x = tmpp[3].x;
	l.p[3].y = tmpp[3].z;
	peresechenie = collideline(l);
	if (peresechenie == 1)					//право верх
	{
		per1 = 1;
		switchcordwall(&tmpp[2], &tmpp[3], &offset[2], setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
			// printf ("%zu 2 %f %f\n", c, offset[2], offset[1]);
		p[2] = tmpp[2];
	}
	// if (per == 1)
	// {
	// 	switchcordwall(&p[1], &p[0], &offset[1], setfvector2d(
	// 	cos(-1.048) * 1000, sin(-1.048) * 1000));
	// 	return (1);
	// }
	// if (c == 99)
	// 	printf("%f %f %f %f \n",offset[0], offset[1],offset[2],offset[3]);
	if (p[0].z <= 0 || p[1].z <= 0 || p[2].z <= 0 || p[3].z <= 0)
		return (0);
	return (1);
}

void	cleartexture(t_window *win)
{
	t_ivector2d cord;

	cord.y = 0;
	while (cord.y < win->size.y)
	{
		cord.x = 0;
		while (cord.x < win->size.x)
		{
			win->pixels[cord.x + (cord.y * win->size.x)] = 0;
			cord.x++;
		}
		cord.y++;
	}
}

void clipforfloor(t_player *player, t_fvector *p, float *topleft, float *topright)
{
	float		t1;
	float		t2;
	int 		*mask;
	t_fvector2d ret;
	t_fvector	*chek;
	t_fvector	 tmpp[4];
	t_line l;
	t_line cline;
	float offset;
	int i;
	int e;
	i = 0;
	float pos;
	float pos1;
	float pos2;
	int peresechenie;
	float x, y;
	
	
	peresechenie = 1;
	// mask = (int *)malloc(sizeof(int) * 4);
	// while (i < 4)
	// {
	// 	mask[i] = 0;
	// 	i++;
	// }
	i = 0;
	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(-1.0471975512/2.0) * 1000.0;
	l.p[1].y = sin(-1.0471975512/2.0) * 1000.0;
	while (i < 4)
	{
		l.p[2].x = p[i].z;
		l.p[2].y = p[i].x;
		l.p[3].x = p[i+1 == 4 ? 0 : i+1].z;
		l.p[3].y = p[i+1 == 4 ? 0 : i+1].x;
		peresechenie = collideline(l);
		if (peresechenie == 1)
		{
			// printf("%f %f\n", p[i].x, p[i].z);
			switchcordwall(&p[i], &p[i+1 == 4 ? 0 : i+1], &offset, setfvector2d(
			cos(-1.0471975512) * 1000, sin(-1.0471975512) * 1000));
			offset = 1.0-offset;
			if (i == 0)
			{
				topleft[0] = 0;
				topleft[1] = offset;
			}
			if (i == 2)
			{
				topleft[0] = 1;
				topleft[1] = offset;
			}
			if (i == 1)
			{
				topleft[0] = offset;
				topleft[1] = 1;
			}
			if (i == 3)
			{
				topleft[0] = offset;
				topleft[1] = 0;
			}
			e = i;
				// printf("%d ", i);
			break ;
			// printf("%f %f\n\n", p[i].x, p[i].z);
			
			// return (setfvector(0, p[i].y, ret.x, 1));
		}
		i++;
	}
	i = 0;
	l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(1.0471975512) * 1000;
	l.p[1].y = sin(1.0471975512) * 1000;
	while (i < 4)
	{
		l.p[2].x = p[i].x;
		l.p[2].y = p[i].z;
		l.p[3].x = p[i+1 == 4 ? 0 : i+1].x;
		l.p[3].y = p[i+1 == 4 ? 0 : i+1].z;
		peresechenie = collideline(l);
		if (peresechenie == 1)
		{
			// printf("%f %f\n", p[i].x, p[i].z);
			switchcordwall(&p[i+1 == 4 ? 0 : i+1], &p[i], &offset, setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
			offset = 1.0-offset;
			// printf("%f \n", offset);
			if (i == 0)
			{
				topright[0] = 0;
				topright[1] = offset;
			}
			if (i == 2)
			{
				topright[0] = 1;
				topright[1] = offset;
			}
			if (i == 1)
			{
				topright[0] = offset;
				topright[1] = 1;
			}
			if (i == 3)
			{
				topright[0] = offset;
				topright[1] = 0;
			}
			break ; 
			// return (setfvector(0, p[i].y, ret.x, 1));
		}
		i++;
	}
	// if (e % 2 == i % 2 && i != e)
	// 	mask[i - 1 == -1 ? 3 : i-1] = 1;
	// if (e != i)
	// 	mask[i] = 1;
	// printf("%d %d !!! %d %d %d %d\n", e, i, mask[0], mask[1], mask[2], mask[3]);
	// return (mask);
}
void	swap_float(float *a, float *b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
t_fvector    raycastfloor(t_fvector2d angle, t_fvector2d yse)
{
    t_fvector    res;
    t_fvector    step;

    step.y = (yse.y - yse.x) / sin(angle.y);
    res.y = yse.y;
    res.z = step.y * cos(angle.y);
    step.z = res.z / cos(angle.x);
    res.x = step.z * sin(angle.x);
    return (res);
}

void	drawsectorv2(uint32_t *p, t_player play, t_fvector *w, size_t count, size_t floor, size_t ceil, t_rgb colorfloor, t_rgb colorceil, size_t i, t_tga texture)
{
	t_wall		wa;
	double		offloor[4];
	float		vec;
	t_fvector	delta;
	t_fvector	tmpp[4];
	float		offset[4];
	t_rgb		color;
	t_mat4x4	cammat;
	t_mat4x4	projec;
	size_t		c;
	t_fvector2d	r;
	int			s;
	t_fvector	fl[4];
	int x;
	t_rgb color1;
	float dx;
	float dy;
	float maxdelt;
	float offloorright[2];
	float offloorleft[2];
	float topleft[2];
	float topright[2];
	int kef;
	int *mask;
	x = 0;
	c = 0;
	cammat = matcam(&play);
	projec = matprojection(initcam(setivector2d(800, 800)));

	//calculate floor
	t_fvector2d min;
	t_fvector2d max;

	min = setfvector2d(w[0].x, w[0].y);
	max = setfvector2d(w[0].x, w[0].y);
	while (c < count)
	{
		min.x = ft_fmin(min.x, w[c].x);
		min.y = ft_fmin(min.y, w[c].y);
		max.x = ft_fmax(max.x, w[c].x);
		max.y = ft_fmax(max.y, w[c].y);
		c++;
	}
	// if (i == 0)
	t_fvector a = raycastfloor(setfvector2d(1.0471975512, -1.0471975512), setfvector2d(play.pos.y, floor));
	t_fvector b = raycastfloor(setfvector2d(-1.0471975512, -1.0471975512), setfvector2d(play.pos.y, floor));
	
	wa.p[0] = setfvector(min.x, floor, min.y, 1);
	wa.p[1] = setfvector(min.x, floor, max.y, 1);
	wa.p[2] = setfvector(max.x, floor, max.y, 1);
	wa.p[3] = setfvector(max.x, floor, min.y, 1);
	maxdelt = fabsf (wa.p[2].x - wa.p[0].x);
	dx = fabsf(max.x - min.x);
	dy = fabsf(max.y - min.y);
	// if (fabsf(wa.p[2].z - wa.p[0].z) > fabsf(wa.p[2].x - wa.p[0].x))
	// 	maxdelt = fabsf (wa.p[2].z - wa.p[0].z);
	multmatrixdrawwall(wa.p, cammat);
	
	// dx = sqrt((dx * dx) + (dy * dy));
	offloor[0] = fabsf((play.pos.z - min.y) / dy); // x
	offloor[1] = fabsf((play.pos.x - min.x) / dx);	// y
	
	if (i == 0)
	{
		offloorright[0] = ((a.x + play.pos.z - min.y) / dy);
		offloorright[1] = ((a.z *3 + play.pos.x - min.x) / dx);
		offloorleft[0] = ((b.x + play.pos.z - min.y) / dy);
		offloorleft[1] = ((b.z *3+ play.pos.x - min.x) / dx);
		// if (i == 0)
			// printf("%f\n", offloorright[1]);
	printf("%f %f %f %f %f %f\n", offloorleft[0], offloorleft[1]  ,offloorright[0],offloorright[1], play.pos.x , min.y);
	}

	fl[0] = wa.p[0];
	fl[1] = wa.p[3];
	fl[2] = wa.p[2];
	fl[3] = wa.p[1];
	
	if (i == 0)
		clipforfloor(&play, fl, topleft, topright);
	
	fl[0] = multipmatrix(fl[0], projec);
	fl[0] = divfvector(fl[0], fl[0].w, fl[0].w, fl[0].w);
	fl[0] = addfvector(fl[0], 1, 1, 0);
	fl[0] = multfvector(fl[0], 400, 400, 1);
	fl[1] = multipmatrix(fl[1], projec);
	fl[1] = divfvector(fl[1], fl[1].w, fl[1].w, fl[1].w);
	fl[1] = addfvector(fl[1], 1, 1, 0);
	fl[1] = multfvector(fl[1], 400, 400, 1);
	fl[2] = multipmatrix(fl[2], projec);
	fl[2] = divfvector(fl[2], fl[2].w, fl[2].w, fl[2].w);
	fl[2] = addfvector(fl[2], 1, 1, 0);
	fl[2] = multfvector(fl[2], 400, 400, 1);
	fl[3] = multipmatrix(fl[3], projec);
	fl[3] = divfvector(fl[3], fl[3].w, fl[3].w, fl[3].w);
	fl[3] = addfvector(fl[3], 1, 1, 0);
	fl[3] = multfvector(fl[3], 400, 400, 1);
	s = 0;
	// while (s < 4)
	// {
	// 	fl[s].z = mask[s];
	// 	s++;
	// }
	// free(mask);
	// if (i == 0)
	// 	printf("%f %f %f %f\n", fl[0].w,  fl[1].w, fl[2].w, fl[3].w);
	if (i == 0)
		drawfloor1(p, wa, color1, play, offloor, fl, offloorright, offloorleft, topleft, topright);

		
	c = 0;
	
	while (c < count)
	{
		wa.p[0] = setfvector(w[c].x, floor, w[c].y, 1);
		wa.p[1] = setfvector(w[c + 1 >= count ? 0 : c + 1].x, floor, w[c + 1 >= count ? 0 : c + 1].y, 1);
		wa.p[2] = addfvector(wa.p[0], 0, ceil, 0);
		wa.p[3] = addfvector(wa.p[1], 0, ceil, 0);
		multmatrixdrawwall(wa.p, cammat);
		offset[0] = 1;
		offset[1] = 1;
		offset[2] = 1;
		offset[3] = 1;

		if (clip(&play, wa.p, offset, c))
		{
			wallproj(wa.p, projec);
			if (w[c].z == -1)
				color = setrgb(255, 255, 255);
			else
				color = setrgb(255, 0, 0);
			if (wa.p[0].x > wa.p[1].x)
			{
				ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);				
				swap_float(&offset[1], &offset[0]);
			}
			if (wa.p[2].x > wa.p[3].x)
			{
				ft_swap((void**)&wa.p[2], (void**)&wa.p[3]);
				swap_float(&offset[3], &offset[2]);
			}
			
			// if (c == 5)
			//	printf ("%zu niz %f\n", c, offset[0]);
			// if (w[c].z == -1)			
			// 	drow_wall(p, wa, texture, offset, play.rotate.x);
			// printf ("%f %f %f %f\n", fl.x, fl.y, fl.z, fl.w);
			
				// drawline(p, fl[0], fl[1], color);
			drawline(p, wa.p[0], wa.p[1], color);
			drawline(p, wa.p[0], wa.p[2], color);
			drawline(p, wa.p[2], wa.p[3], color);
			drawline(p, wa.p[1], wa.p[3], color);
		}
		c++;
		
		// color1 = setrgb(255, 0, 255);
	}
	color1 = setrgb(255, 0, 255);
	if (i == 0)
	{
		if (fl[1].x < 800 && fl[1].x > 0 && fl[1].y > 0 && fl[1].y < 800)
			p[(int)fl[1].x + ((int)fl[1].y * 800)] = ((((((255 << 8) | 255) << 8) | 0) << 8) | 243);
		if (fl[3].x < 800 && fl[3].x > 0 && fl[3].y > 0 && fl[3].y < 800)
			p[(int)fl[3].x + ((int)fl[3].y * 800)] = ((((((255 << 8) | 255) << 8) | 0) << 8) | 243);
	}
	// free(fl);
}

void	draw(t_doom *doom)
{
	t_rgb	colorfloor;
	t_rgb	colorceil;
	int		i;

	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	i = doom->thismap.sectorcount - 1;
	clock_t start = clock();
	while (i > -1)
	{
		switch (i)
		{
			case 0:
				colorfloor = setrgb(0, 0, 255);
				colorceil = setrgb(150, 150, 150);
				break;
			case 1:
				colorfloor = setrgb(0, 255, 0);
				colorceil = setrgb(0, 150, 150);
				break;
			case 2:
				colorfloor = setrgb(255, 0, 0);
				colorceil = setrgb(0, 0, 150);
				break;
			default:
				colorfloor = setrgb(255, 255, 255);
				colorceil = setrgb(50, 50, 50);
				break;
		}
		// if (doom->thismap.sectors[i].floor == 3)
		// doom->thismap.sectors[i].floor = 1;
		
		drawsectorv2(doom->win->pixels, doom->player, doom->thismap.walls +
		doom->thismap.sectors[i].start,
		doom->thismap.sectors[i].count,
		doom->thismap.sectors[i].floor,
		doom->thismap.sectors[i].height, colorfloor, colorceil, i, doom->texture[doom->thismap.sectors[i].walltexture]);
		
		// printf ("%d \n", doom->thismap.sectors[i].floor);
		i--;
	}
	// drawobj(doom, doom->thismap);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	// printf("The time: %f seconds\n", seconds);
	
	// printf ("\n");
	// colorfloor = setrgb(0, 0, 255);
	// colorceil = setrgb(150, 150, 150);
	// drawsectorv2(doom->win->pixels, doom->player, doom->thismap.walls +
	// doom->thismap.sectors[doom->player.sector].start,
	// doom->thismap.sectors[doom->player.sector].count,
	// doom->thismap.sectors[doom->player.sector].floor,
	// doom->thismap.sectors[i].height, colorfloor, colorceil, doom->player.sector);
	
	drawminimap(doom->win->pixels, doom, doom->player.sector,
	setivector2d(400, 300));


	drawui(doom);
	// drawrect(doom);

	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_SetRenderDrawColor(doom->win->renderer, 0, 0, 0, 255);
	SDL_RenderPresent(doom->win->renderer);
}
