#include "doom.h"

t_fvector    raycastfloor1(t_fvector2d angle, t_fvector2d yse)
{
    t_fvector    res;
    t_fvector    step;

	float xt;
	float dir;
	float dist;
	float yt;
	dir = angle.y;
	xt = ((yse.y - yse.x) / sin(dir)) * cos(dir);
	dist =  pow(pow(xt, 2) + pow(yse.y - yse.x, 2), 0.5);
	yt = dist * cos(angle.x);
	res.x =  dist * sin(angle.x);
	res.z =  dist * cos(angle.x);
    return (res);
}

void    dots_floor(t_fvector *w, size_t count, t_floor *for_floor,  t_player play)
{
    int c;
    t_mat4x4	cammat;

    cammat = matcam(&play);
    c = 0;
	for_floor->min = setfvector2d(w[0].x, w[0].y);
	for_floor->max = setfvector2d(w[0].x, w[0].y);
    while (c < count)
	{
		for_floor->min.x = ft_fmin(for_floor->min.x, w[c].x);
		for_floor->min.y = ft_fmin(for_floor->min.y, w[c].y);
		for_floor->max.x = ft_fmax(for_floor->max.x, w[c].x);
		for_floor->max.y = ft_fmax(for_floor->max.y, w[c].y);
		c++;
	}
    for_floor->wa.p[0] = setfvector(for_floor->min.x, for_floor->floor, for_floor->min.y, 1);
	for_floor->wa.p[3] = setfvector(for_floor->min.x, for_floor->floor, for_floor->max.y, 1);
	for_floor->wa.p[2] = setfvector(for_floor->max.x, for_floor->floor, for_floor->max.y, 1);
	for_floor->wa.p[1] = setfvector(for_floor->max.x, for_floor->floor, for_floor->min.y, 1);
    for_floor->dx = fabsf(for_floor->max.x - for_floor->min.x);
	for_floor->dy = fabsf(for_floor->max.y - for_floor->min.y);
    multmatrixdrawwall(for_floor->wa.p, cammat);
}

void    offsetts_floor(t_floor *for_floor, t_player play)
{
    for_floor->a = raycastfloor1(setfvector2d(1.0471975512 + play.rotate.z,
        -1.0471975512 + play.rotate.x), setfvector2d(play.pos.y, for_floor->floor));
	for_floor->b = raycastfloor1(setfvector2d(-1.0471975512 + play.rotate.z,
        -1.0471975512 + play.rotate.x), setfvector2d(play.pos.y, for_floor->floor));
    for_floor->offloorright[0] = ((for_floor->a.x + play.pos.z - for_floor->min.y) / for_floor->dy);
    for_floor->offloorright[1] = ((for_floor->a.z + play.pos.x - for_floor->min.x) / for_floor->dx);
    for_floor->offloorleft[0] = ((for_floor->b.x + play.pos.z - for_floor->min.y) / for_floor->dy);
    for_floor->offloorleft[1] = ((for_floor->b.z + play.pos.x - for_floor->min.x) / for_floor->dx);
	for_floor->posplay[0] = ((play.pos.z - for_floor->min.y) / for_floor->dy);
	for_floor->posplay[1] = ((play.pos.x - for_floor->min.x) / for_floor->dx);
	if (for_floor->offloorleft[0] < 0 || for_floor->offloorleft[0] > 1)
		for_floor->offloorleft[0] = for_floor->offloorleft[0] < 0 ? 0 : 1;
	if (for_floor->offloorleft[1] < 0 || for_floor->offloorleft[1] > 1)
		for_floor->offloorleft[1] = for_floor->offloorleft[1] < 0 ? 0 : 1;
	if (for_floor->offloorright[0] < 0 || for_floor->offloorright[0] > 1)
		for_floor->offloorright[0] = for_floor->offloorright[0] < 0 ? 0 : 1;
	if (for_floor->offloorright[1] < 0 || for_floor->offloorright[1] > 1)
		for_floor->offloorright[1] = for_floor->offloorright[1] < 0 ? 0 : 1;
}

void    mnogoifleft(int i,  t_floor *for_floor, float offset)
{
    if (i == 0)
	{
		for_floor->topleft[0] = 0;
		for_floor->topleft[1] = offset;
	}
    if (i == 2)
   	{
    	for_floor->topleft[0] = 1;
		for_floor->topleft[1] = 1.0 - offset;
	}
	if (i == 1)
	{
		for_floor->topleft[0] = offset;
		for_floor->topleft[1] = 1;
	}
	if (i == 3)
	{
		for_floor->topleft[0] = 1.0 - offset;
		for_floor->topleft[1] = 0;
	}
}

void    mnogoifright(int i,  t_floor *for_floor, float offset)
{
    if (i == 0)
	{
		for_floor->topright[0] = 0;
		for_floor->topright[1] = 1.0 - offset;
	}
    if (i == 2)
   	{
    	for_floor->topright[0] = 1;
		for_floor->topright[1] = offset;
	}
	if (i == 1)
	{
		for_floor->topright[0] = 1.0 - offset;
		for_floor->topright[1] = 1;
	}
	if (i == 3)
	{
		for_floor->topright[0] = offset;
		for_floor->topright[1] = 0;
	}
}

void    clip_floor_left(t_player play, t_floor *for_floor)
{
	t_line l;
	int i;
	float offset;
    i = 0;
    l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(-1.0471975512/2.0) * 1000.0;
	l.p[1].y = sin(-1.0471975512/2.0) * 1000.0;
    while (i < 4)
	{
		l.p[2].x = for_floor->wa.p[i].z;
		l.p[2].y = for_floor->wa.p[i].x;
		l.p[3].x = for_floor->wa.p[i+1 == 4 ? 0 : i+1].z;
		l.p[3].y = for_floor->wa.p[i+1 == 4 ? 0 : i+1].x;
		if (collideline(l))
		{	
			switchcordwall(&for_floor->wa.p[i], &for_floor->wa.p[i+1 == 4 ? 0 : i+1], &offset, setfvector2d(
			cos(-1.0471975512) * 1000, sin(-1.0471975512) * 1000));
            mnogoifleft(i,  for_floor, 1.0 - offset);
			break ;
		}
		i++;
	}
}
void    clip_floor_right(t_player play, t_floor *for_floor, t_floor *for_floorduble)
{
	t_line l;
	int i;
	float offset;

    i = 0;
    l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(1.0471975512) * 1000.0;
	l.p[1].y = sin(1.0471975512) * 1000.0;
    while (i < 4)
	{
		l.p[2].x = for_floor->wa.p[i].x;
		l.p[2].y = for_floor->wa.p[i].z;
		l.p[3].x = for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x;
		l.p[3].y = for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].z;
		if (collideline(l))
		{
			switchcordwall(&for_floor->wa.p[i + 1 == 4 ? 0 : i+1],&for_floor->wa.p[i], &offset, setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
            mnogoifright(i,  for_floorduble, 1.0 - offset);
			for_floorduble->wa.p[i + 1 == 4 ? 0 : i+1] = for_floor->wa.p[i + 1 == 4 ? 0 : i+1];
			break ;
		}
		i++;
	}
}
void    clip_floor_left2(t_player play, t_floor *for_floor)
{
	t_line l;
	int i;
	float offset;
    i = 0;
    l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(-1.0471975512/2.0) * 1000.0;
	l.p[1].y = sin(-1.0471975512/2.0) * 1000.0;
    while (i < 4)
	{
		l.p[2].x = for_floor->wa.p[i].z;
		l.p[2].y = for_floor->wa.p[i].x;
		l.p[3].x = for_floor->wa.p[i+1 == 4 ? 0 : i+1].z;
		l.p[3].y = for_floor->wa.p[i+1 == 4 ? 0 : i+1].x;
		if (collideline(l))
		{	
			// switchcordwall(&for_floor->wa.p[i], &for_floor->wa.p[i+1 == 4 ? 0 : i+1], &offset, setfvector2d(
			// cos(-1.0471975512) * 1000, sin(-1.0471975512) * 1000));
            // mnogoifleft(i,  for_floor, 1.0 - offset);
			// break ;
		}
		i++;
	}
}

void	ft_intzero(int *array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		array[i] = 0;
		i++;
	}
}
void    clip_floor_right2(t_player play, t_floor *for_floor, t_floor *for_floorduble)
{
	t_line l;
	int i;
	float offset;
	int	peresec[2];
	t_fvector tmp;
	int e;

	e = 0;
    i = 0;
    l.p[0].x = 0;
	l.p[0].y = 0;
	l.p[1].x = cos(1.0471975512) * 1000.0;
	l.p[1].y = sin(1.0471975512) * 1000.0;
    while (i < 4)
	{
		l.p[2].x = for_floor->wa.p[i].x;
		l.p[2].y = for_floor->wa.p[i].z;
		l.p[3].x = for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].x;
		l.p[3].y = for_floor->wa.p[i + 1 == 4 ? 0 : i + 1].z;
		if (collideline(l))
		{
			peresec[e] = i;
			e++;
			printf("%d \n", i);
			

		}
		i++;
	}
		if( (peresec[0] + peresec[1])  == 4 )
		{
			i = peresec[0];
			switchcordwall(&for_floor->wa.p[i + 1 == 4 ? 0 : i+1],&for_floor->wa.p[i], &offset, setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
			// mnogoifright(i,  for_floorduble, 1.0 - offset);
			
			tmp = for_floorduble->wa.p[i + 1 == 4 ? 0 : i+1];
			for_floorduble->wa.p[i + 1 == 4 ? 0 : i+1] = for_floor->wa.p[i + 1 == 4 ? 0 : i+1];
			for_floor->wa.p[i + 1 == 4 ? 0 : i+1] = tmp;
			i = peresec[1];
			switchcordwall(&for_floor->wa.p[i],&for_floor->wa.p[i + 1 == 4 ? 0 : i+1], &offset, setfvector2d(
			cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
			mnogoifright(i,  for_floorduble, 1.0 - offset);
			
			tmp = for_floorduble->wa.p[i + 1 == 4 ? 0 : i+1];
			for_floorduble->wa.p[i + 1 == 4 ? 0 : i+1] = for_floor->wa.p[i + 1 == 4 ? 0 : i+1];
			for_floor->wa.p[i + 1 == 4 ? 0 : i+1] = tmp;
		}
		// else
		// {
		// 	switchcordwall(&for_floor->wa.p[i], &for_floor->wa.p[i + 1 == 4 ? 0 : i+1], &offset, setfvector2d(
		// 	cos(1.0471975512) * 1000, sin(1.0471975512) * 1000));
		// 	mnogoifright(i,  for_floorduble, 1.0 - offset);
		// 	tmp = for_floorduble->wa.p[i];
		// 	for_floorduble->wa.p[i] = for_floor->wa.p[i];
		// 	for_floor->wa.p[i] = tmp;
		// }
	// clip_other_sector();

}

void    calculate_floor(t_player play,t_fvector *w, uint32_t *p, t_tga texture, size_t count, size_t floor)
{
    t_floor for_floor;
	t_floor for_floorduble;
	t_mat4x4	projec;
    for_floor.floor = floor;

    projec = matprojection(initcam(setivector2d(800, 800)));
    dots_floor(w, count, &for_floor, play);
    offsetts_floor(&for_floor, play);
	for_floorduble = for_floor;
	if (for_floor.posplay[0] > 0 && for_floor.posplay[0] < 1 && for_floor.posplay[1] > 0 && for_floor.posplay[1] < 1)
	{
		clip_floor_left(play, &for_floor);
		clip_floor_right(play, &for_floorduble, &for_floor);
		wallproj(for_floor.wa.p, projec);
		drow_floor(&for_floor , p, texture);
	}
	else
	{
		// clip_floor_left2(play, &for_floor);
		clip_floor_right2(play, &for_floorduble, &for_floor);
		wallproj(for_floor.wa.p, projec);
		printf("%f %f %f %f\n", for_floor.wa.p[0].x, for_floor.wa.p[1].x, for_floor.wa.p[2].x, for_floor.wa.p[3].x);
		printf("%f %f %f %f\n", for_floor.wa.p[0].y, for_floor.wa.p[1].y, for_floor.wa.p[2].y, for_floor.wa.p[3].y);
	}
	
    return;
}