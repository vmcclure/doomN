#include "doom.h"

void	put_dots(t_dot *dot, t_floor *for_floor, uint32_t *p)
{
	int i;
	int start;
	int end;
	float dy;
	float x;
	float dx;
	float y;
	
	start = -1;
	end = -1;
	x = 0;
	i = 0;
	printf ("%f %f %f %f \n", for_floor->wa.p[0].x, for_floor->wa.p[1].x, for_floor->wa.p[2].x, for_floor->wa.p[3].x);
	printf ("%f %f %f %f \n", for_floor->wa.p[0].y, for_floor->wa.p[1].y, for_floor->wa.p[2].y, for_floor->wa.p[3].y);
	printf ("%f %f %f %f \n", for_floor->wa.p[0].w, for_floor->wa.p[1].w, for_floor->wa.p[2].w, for_floor->wa.p[3].w);
	while (i < 4)
	{
		if (for_floor->wa.p[i].w > 0 && for_floor->wa.p[i].x < 0 && for_floor->wa.p[i].x > -1)
			start = i;
		if (for_floor->wa.p[i].w > 0 && for_floor->wa.p[i].x > 800 && for_floor->wa.p[i].x < 801)
			end = i;
		i++;
	}
	i = start;
	x = for_floor->wa.p[i].x;
	while (i != end)
	{	
		x = for_floor->wa.p[i].x;
		y =	for_floor->wa.p[i].y;
		dx = for_floor->wa.p[i].x - for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x;
		dy = for_floor->wa.p[i].y - for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].y;
		dy = dy/dx;
		while (x < for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x && x < 800)
		{
			dot->verh[(int)x].x = x;
			y = y + dy;
			dot->verh[(int)x].y = y;
			x++;
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
	float dir;
	r = 255;
	g = 0;
	b = 0;
	// while (i < 800)
	// {
	// 	x = dot->verh[(int)i].x;
	// 	y = dot->verh[(int)i].y;
	// 	while (y < 800)
	// 	{
	// 		p[(int)x + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
	// 		y++;
	// 	}
	// 	i++;
	// }
}

void    drow_floor(t_floor *for_floor, uint32_t *p)
{
    t_dot		dot;
	int			i;
	put_dots(&dot, for_floor, p);

}