#include "doom.h"

void	dot_target(float *target, t_floor *for_floor)
{
	if (for_floor->topleft[0] == 0)
	{
		target[0] = 0;
		target[1] = 1;
	}
	if (for_floor->topleft[0] == 1)
	{
		target[0] = 1;
		target[1] = 0;
	}
	if (for_floor->topleft[1] == 0)
	{
		target[0] = 0;
		target[1] = 0;
	}
	if (for_floor->topleft[1] == 1)
	{
		target[0] = 1;
		target[1] = 1;
	}
}
void	dot_target2(float *target, t_floor *for_floor)
{
	if (for_floor->topright[0] == 0)
	{
		target[0] = 0;
		target[1] = 0;
	}
	if (for_floor->topright[0] == 1)
	{
		target[0] = 1;
		target[1] = 1;
	}
	if (for_floor->topright[1] == 0)
	{
		target[0] = 1;
		target[1] = 0;
	}
	if (for_floor->topright[1] == 1)
	{
		target[0] = 0;
		target[1] = 1;
	}
}
void	put_this_sector(t_dot *dot, t_floor *for_floor, uint32_t *p, t_tga *image1)
{
	int i;
	int start;
	int end;
	float dy;
	float x;
	float dx;
	float y;
	float niztexdx;
	float niztexdy;
	float verhtexdx;
	float verhtexdy;
	float target[2];
	float target2[2];
	float dxtext;
	float dytext;
	float k;
	float startpixel[2];
	start = -1;
	end = -1;
	x = 0;
	i = 0;
	while (i < 4)
	{
		if (for_floor->wa.p[i].w > 0 && for_floor->wa.p[i].x < 0 && for_floor->wa.p[i].x > -1 && for_floor->posplay[0] > 0
			&& for_floor->posplay[0] < 1 && for_floor->posplay[1] > 0 && for_floor->posplay[1] < 1)
			start = i;
		if (for_floor->wa.p[i].w > 0 && for_floor->wa.p[i].x > 800 && for_floor->wa.p[i].x < 801 && for_floor->posplay[0] < 1 
			&& for_floor->posplay[0] > 0 && for_floor->posplay[1] > 0 && for_floor->posplay[1] < 1)
			end = i;
		i++;
	}
	if (start == -1 || end == -1)
		return;
	dot_target(target, for_floor);
	dot_target2(target2, for_floor);
	i = start;
	x = for_floor->wa.p[i].x;
	niztexdx = for_floor->offloorleft[0] - for_floor->offloorright[0];
	niztexdx = niztexdx / 800.0;
	niztexdy = for_floor->offloorleft[1] - for_floor->offloorright[1];
	niztexdy = niztexdy / 800.0;
	while (i != end)
	{

		x = for_floor->wa.p[i].x;
		y =	for_floor->wa.p[i].y;
		dx = for_floor->wa.p[i].x - for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x;
		dy = for_floor->wa.p[i].y - for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].y;
		dy = dy/dx;
		if (i == start)
		{
			verhtexdx = for_floor->topleft[0] - target[0];
			verhtexdx = verhtexdx/dx;
			verhtexdy = for_floor->topleft[1] - target[1];
			verhtexdy = verhtexdy/dx;
			startpixel[0] = for_floor->topleft[0];
			startpixel[1] = for_floor->topleft[1];
		}
		if (i != start && (target[0] != target2[0] || target[1] != target2[1]))
		{
			verhtexdx = target[0] - target2[0];
			verhtexdx = (verhtexdx/dx);
			verhtexdy = target2[1] - target[1];
			verhtexdy = verhtexdy/dx;
			startpixel[0] = target[0];
			startpixel[1] = target[1];
		}
		if((i + 1 == 4 ? 0 : i + 1) == end)
		{
			verhtexdx = target2[0] - for_floor->topright[0];
			verhtexdx = verhtexdx/dx;
			verhtexdy = target2[1] - for_floor->topright[1];
			verhtexdy = verhtexdy/dx;
			startpixel[0] = target2[0];
			startpixel[1] = target2[1];
		}
		if ((start + 1 == 4 ? 0 : start + 1)  == end)
		{
			verhtexdx = for_floor->topleft[0] - for_floor->topright[0];
			verhtexdx = verhtexdx/dx;
			verhtexdy = for_floor->topleft[1] - for_floor->topright[1];
			verhtexdy = verhtexdy/dx;
			startpixel[0] = for_floor->topleft[0];
			startpixel[1] = for_floor->topleft[1];
			
		}
		
		k = 0;
		while (x < for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x && x < 800)
		{
			y = y + dy;
			dot->verh[(int)x].x = x;
			dot->niz[(int)x].x = x;
			dot->niz[(int)x].y = 800;			
			dot->verh[(int)x].y = y;
			dot->niztext[(int)x].x = for_floor->offloorleft[0] - (niztexdx * x);
			dot->niztext[(int)x].y = for_floor->offloorleft[1] - (niztexdy * x);
			dot->verhtext[(int)x].x = startpixel[0] + verhtexdx * k;
			dot->verhtext[(int)x].y = startpixel[1] + verhtexdy * k;
			x++;
			k++;
		}
		i++;
		if(i == 4)
			i = 0;
	}
	i = 0;
	int r;
	int g;
	int b;
	float xt;
	float dist;
	int xp;
	int yp;
	float dir;
	r = 255;
	g = 0;
	t_tga *image;
	image = tgafloor;
	b = 0;
	while (i < 800)
	{
		x = dot->verh[(int)i].x;
		y = dot->verh[(int)i].y;
		dy = (dot->verh[(int)i].y - dot->niz[(int)i].y);
		dxtext = dot->verhtext[(int)x].x - dot->niztext[(int)x].x;
		dxtext = dxtext/dy;
		dytext = dot->verhtext[(int)x].y - dot->niztext[(int)x].y;
		dytext = dytext/dy;
		while (y < dot->niz[(int)x].y)
		{
			yp =(int)((image->height -1) * (dot->verhtext[(int)i].y + (float)(y - dot->verh[(int)i].y) * dytext));
			xp = (int)((image->width - 1) * (dot->verhtext[(int)i].x + (float)(y - dot->verh[(int)i].y) * dxtext));
			if (xp < image->width && xp >= 0 && yp < image->height && yp >= 0 )
			{
				r = image->pic[yp][(int)xp].red;
				g = image->pic[yp][(int)xp].green;
				b = image->pic[yp][(int)xp].blue;
			}
			else
			{
				r = 0;
				g = 255;
				b = 0;
			}
			p[(int)x + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
			y++;
		}
		i++;
	}
}

void    drow_floor(t_floor *for_floor, uint32_t *p, t_tga texture)
{
    t_dot		dot;
	int			i;
	put_this_sector(&dot, for_floor, p, &texture);
	put_other_sector(&dot, for_floor, p, &texture);
}