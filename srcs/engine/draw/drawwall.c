/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/06/02 21:35:21 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "doom.h"
void brez(float x0, float x1, float y0, float y1, t_tga image,  float xp, int start, uint32_t *p, float *offset, float xp1)
{
	float dx;
	float dy;
	float x;
	float y;
	float xt;
	float d;
	float d1;
	float d2;
	int r;
	int g;
	int b;
	int yp;
	float k;
	float m;
	float e;
	char a;
	float ey;
	float dir;
	float dist;
	e = -1;
	dx = fabs(x1 - x0);
	dy = fabs(y1 - y0);
	d = 2* (dx - dy);
	d1 = 2 * dx;
	d2 = (dx - dy) *2.0;
	ey = 1;
	
	if (x1 < x0)
	 	e *= -1;

	if (start == 2)
		{
			y = y1;
			x = x1;
			ey *= 1;
		}
	if (start == 1)
		{
			y = y0;
			x = x0;
			ey *= -1;
		}
	
	if (ey == -1)
		e *= -1;
	
	float tmp;
	k = dy   / (float)(image.height);
	
	if ((start == 1 && y >= 800))
	{
		
		dir = (atan((float)(dy)/(float)(dx)));
		xt = ((y - 800) / sin(dir)) * cos(dir) + x;
		dist =  pow(pow(xt - x, 2) + pow(800 - y, 2), 0.5);//y - 800.0;//
		x = x + dist * cos(dir) * e ;
		y = y - dist * sin(dir);
		y = 799;
	}
	if ((start == 2 && y < 0))
	{
		dir = (atan((float)(dy)/(float)(dx)));
		xt = ((fabsf(y)) / sin(dir)) * cos(dir) + x;
		dist =  pow(pow(xt - x, 2) + pow(y, 2), 0.5);
		x = x + dist * cos(dir) * e;
		y = y + dist * sin(dir);
		y = 0;
	}
	dist = pow(pow(dx, 2) + pow(dy, 2), 0.5);
	xp1 = xp1/dist;
	while (y <= y0 && y >= y1)
	{
		if ((start == 2 && y >= 800) || (start == 1 && y < 0))
            break ;
		// if ((start == 1 && y >= 800))
		// 	y = 800;
		// if ((start == 2 && y < 0))
		// 	y = 0;
		y += ey; ;
		if (d < 0)
			d +=d1;
		else
		{
			x += e;
			d +=d2;
		}
		
		// xp = (int)((float)((float)x + kef )/m);
		xp = xp + xp1;
		yp =(int)((y - y1)/k);
		if (yp >= 0 && yp < image.height && xp >= 0 && xp < image.width)
		{
			r = image.pic[yp][(int)xp].red;
			g = image.pic[yp][(int)xp].green;
			b = image.pic[yp][(int)xp].blue;
			a = image.pic[yp][(int)xp].alpha;
		}
		if (x >= 0 && x < 800 && y >= 0 && y < 800)
		{
			if (a != 0)
			{
				if (y < y0 && y > y1 && x > 0 && x < 799)
					p[(int)(x+1) + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
					p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
			}
		}
		// SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// 	SDL_RenderDrawPoint (renderer,x, y);
	}
}
void drow_wall(uint32_t *p, t_wall wall, t_tga image, float	*offset, float rotate_x)
{
	int dx1;
	int dy1;
	int dx4;
	int dy4;
	float dist1;
	int dist2;
	float dir1;
	float dir4;
	float k;
	char r;
	char g;
	char b;
	float i;
	long x;
	int y;
	float m[2];
	char a;
	float *stena1_x;
	float *stena1_y;
	float *stena2_x;
	float *stena2_y;

	float *dist_sten;
	float *ugol_sten;
	float shag_dlya_2_steni;
	float shag_dlya_1_steni;
	int maxdist;
	float dist3;
	int x0;
	int y0;
	int x2;
	int y2;
	int x1;
	int y1;
	int xp;
	int yp;
	int mindist;
	int buf;
	int start;
	float xp1;
	float xpdx;
	float distv;
	float distn;
	x = 0;
	
	if( wall.p[0].x > 805 || wall.p[1].x > 805 || wall.p[0].x < -5 || wall.p[1].x < -5 || wall.p[2].x > 805 || wall.p[3].x > 805 || wall.p[2].x < -5 || wall.p[3].x < -5)
		return;
	// if (offset[0] < 1 && offset[1] < 1)
	// {		
	// 	dist2 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5) ;
	// 	dist2 = (float)dist2 / (1.0 - ((1.0 - offset[1]) + (1.0 - offset[0])));
	// 	dist1 = (float)dist2 * (1.0 - offset[0]);
	// 	dist3 = (float)dist2 * (1.0 - offset[1]);
	// 	dir1 = (atan((wall.p[0].y - wall.p[1].y)/(wall.p[0].x - wall.p[1].x)));
	// 	wall.p[0].x = wall.p[0].x - dist1 * cos(dir1);
	// 	wall.p[0].y = wall.p[0].y - dist1 * sin(dir1);
	// 	wall.p[1].x = wall.p[1].x + dist3 * cos(dir1);
	// 	wall.p[1].y = wall.p[1].y + dist3 * sin(dir1);
	// 	// printf ("polpol x0 %f y0 %f x1 %f y1 %f \n", wall.p[0].x, wall.p[0].y, wall.p[1].x, wall.p[1].y);
	// 	}
	// else 
	// {
	// 	if (offset[0] < 1)
	// 	{
	// 		dist2 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5) ;
	// 		dist1 = (float)dist2 / offset[0] - dist2;
	// 		dir1 = (atan((float)(wall.p[0].y - wall.p[1].y)/(float)(wall.p[0].x - wall.p[1].x)));
	// 		wall.p[0].x = wall.p[0].x - dist1 * cos(dir1);
	// 		wall.p[0].y = wall.p[0].y - dist1 * sin(dir1);
	// 	}
		
	// 	if (offset[1] < 1)
	// 	{
	// 		dist2 = pow(pow(wall.p[1].x - wall.p[0].x, 2) + pow(wall.p[1].y - wall.p[0].y, 2), 0.5) ;
	// 		dist1 = (float)dist2 / offset[1] - dist2;
	// 		dir1 = (atan((float)(wall.p[1].y - wall.p[0].y)/(float)(wall.p[1].x - wall.p[0].x)));
	// 		wall.p[1].x = wall.p[1].x + dist1 * cos(dir1);
	// 		wall.p[1].y = wall.p[1].y + dist1 * sin(dir1);
	// 	}
	// }
	// if (offset[2] < 1 && offset[3] < 1)
	// {
		
	// 	dist2 = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y - wall.p[3].y, 2), 0.5) ;
	// 	dist2 = (float)dist2 / (1.0 - ((1.0 - offset[3]) + (1.0 - offset[2])));
	// 	dist1 = (float)dist2 * (1.0 - offset[2]);
	// 	dist3 = (float)dist2 * (1.0 - offset[3]);
	// 	dir1 = (atan((wall.p[3].y - wall.p[2].y)/(wall.p[3].x - wall.p[2].x)));
	// 	wall.p[2].x = wall.p[2].x - dist1 * cos(dir1);
	// 	wall.p[2].y = wall.p[2].y - dist1 * sin(dir1);
	// 	wall.p[3].x = wall.p[3].x + dist3 * cos(dir1);
	// 	wall.p[3].y = wall.p[3].y + dist3 * sin(dir1);
	// 	// printf ("potolok x0 %f y0 %f x1 %f y1 %f \n", wall.p[2].x, wall.p[2].y, wall.p[3].x, wall.p[3].y);
	// 	// m[0] = (((float)maxdist/(offset[0] * offset[1]))) / (float)(image.width);
	// 	// kef[0] = (float)maxdist/(offset[0]* offset[1]) - ((float)maxdist / offset[1]);
	// }
	// else
	// {
	// 	if (offset[2] < 1)
	// 	{
	// 		dist2 = pow(pow(wall.p[2].x - wall.p[3].x, 2) + pow(wall.p[2].y - wall.p[3].y, 2), 0.5) ;
	// 		dist1 = (float)dist2 / offset[2] - dist2;
	// 		dir1 = (atan((wall.p[2].y - wall.p[3].y)/(wall.p[2].x - wall.p[3].x)));
	// 		wall.p[2].x = wall.p[2].x - (float)dist1 * cos(dir1);
	// 		wall.p[2].y = wall.p[2].y - (float)dist1 * sin(dir1);
	// 	}
	// 	if (offset[3] < 1)
	// 	{
	// 		dist2 = pow(pow(wall.p[3].x - wall.p[2].x, 2) + pow(wall.p[3].y - wall.p[2].y, 2), 0.5) ;
	// 		dist1 = (float)dist2 / offset[3] - dist2;
	// 		dir1 = (atan((wall.p[3].y - wall.p[2].y)/(wall.p[3].x - wall.p[2].x)));
	// 		wall.p[3].x = wall.p[3].x + (float)dist1 * cos(dir1);
	// 		wall.p[3].y = wall.p[3].y + (float)dist1 * sin(dir1);
	// 	}
	// }


	dx1 = (wall.p[1].x - wall.p[0].x);
	dy1 = (wall.p[1].y - wall.p[0].y);
	dx4 = (wall.p[3].x - wall.p[2].x);
	dy4 = (wall.p[3].y - wall.p[2].y);
	dist1 = pow(pow(wall.p[0].x - wall.p[1].x, 2) + pow(wall.p[0].y - wall.p[1].y, 2), 0.5);
	dist2 = pow(pow(wall.p[3].x - wall.p[2].x, 2) + pow(wall.p[3].y - wall.p[2].y, 2), 0.5);

	if (abs(dx4) > abs(dx1))
	{
		maxdist = abs(dx4);
		start = 2;
		mindist = abs(dx1);
		shag_dlya_1_steni = (float)mindist / (float)maxdist;
		shag_dlya_2_steni = 1.0;
	}
	else
	{
		maxdist = abs(dx1);
		start = 1;
		mindist = abs(dx4);
		shag_dlya_1_steni = 1.0;
		shag_dlya_2_steni = (float)mindist / (float)maxdist;
	}
	dir1 = (atan((float)dy1/(float)dx1));
	dir4 = (atan((float)dy4/(float)dx4));
	stena1_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena1_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	i = 0;
	while (i < maxdist)
	{
		stena1_x[(int)i] = wall.p[0].x + (i * shag_dlya_1_steni);
		stena1_y[(int)i] = wall.p[0].y + (i * shag_dlya_1_steni * ((float)dist1/(float)dx1)) * sin(dir1);
		stena2_x[(int)i] = wall.p[2].x + (i * shag_dlya_2_steni);
		stena2_y[(int)i] = wall.p[2].y + (i * shag_dlya_2_steni * ((float)dist2/(float)dx4)) * sin(dir4);
		if (stena1_x[(int)i] < 0 && stena2_x[(int)i] < 0)
			x = i;
		i++;
	}
	// printf ("%d\n", maxdist);
	m[0] = ((float)maxdist) / (float)(image.width);
	m[1] = ((float)maxdist) / (float)(image.width);

	// printf ("1 - %f\n", offset[1]);
	// printf ("1 - %f\n", offset[1]);
	float kef[2];
	kef[0] = 0;
	kef[1] = 0;
	distn = 0;
	distv = 0;
	if (offset[1] < 1)
	{
		kef[0] = 0;//(float)maxdist/offset[1] - (float)maxdist;
		m[0] = (((float)maxdist/offset[1])) / (float)(image.width);
	}
	if (offset[3] < 1)
	{
		kef[1] = 0;//(float)maxdist/offset[1] - (float)maxdist;
		m[1] = (((float)maxdist/offset[3])) / (float)(image.width);
	}
	if (offset[0] < 1)
	{
		kef[0] = (float)maxdist/offset[0] - (float)maxdist;
		m[0] = (((float)maxdist/offset[0])) / (float)(image.width);
	}
	if (offset[2] < 1)
	{
		kef[1] = (float)maxdist/offset[2] - (float)maxdist;
		m[1] = (((float)maxdist/offset[2])) / (float)(image.width);
	}
	
	if (offset[1] < 1 && offset[0] < 1)
	{
		
		distn = (float)maxdist/ (1.0 - ((1.0 - offset[1]) + (1.0 - offset[0])));

		m[0] = (float)distn / (float)(image.width);
		kef[0] = distn * (1.0 - offset[0]);
	}
	if (offset[2] < 1 && offset[3] < 1)
	{
		distv = (float)maxdist/ (1.0 - ((1.0 - offset[3]) + (1.0 - offset[2])));
		m[1] = (float)distv / (float)(image.width);//(offset[2] * offset[3]))) / (float)(image.width);
		kef[1] = distv * (1.0 - offset[2]);
	}
	if (distv > distn)
		start = 2;
	if (distv < distn)
		start = 1;
		float dir;
	dir =1.0-( fabsf(dir1) - fabsf(dir4));
	// x = 0;
	// printf("nizl %f verl %f nizp %f verp %f start %d\n", offset[0], offset[2], offset[1], offset[3], start);
	while (x < maxdist)// && (stena1_x[(int)x] < 800 || stena2_x[(int)x] < 800))
	{
		printf("ln %f lv %f pn %f pv %f %d %f %f\n", offset[0], offset[2], offset[1], offset[3], start, dir , dir4);
		if (start == 2)
		{
			
			xp1 = (int)((float)((float)x + kef[0])/m[0]);
			xp = (int)((float)((float)x + kef[1] )/m[1]);
			xpdx = (xp1 - xp);
		}
		else 
		{
			// printf("%f %f %f %f %d \n", offset[0], offset[1], offset[2], offset[3], maxdist);
			xp = (int)((float)((float)x + kef[0]) /m[0]);
			xp1 = (int)((float)((float)x + kef[1]) /m[1]);
			xpdx = (xp1 - xp);
		}
		
		// if  (rotate_x > 0 && distv < distn)
		// {	
		// 	printf("1\n");
		// 	xp1 = (int)((float)((float)x + kef[0] )/m[0]);
		// 	xp = (int)((float)((float)x + kef[1] )/m[1]);
		// 	xpdx = (xp1 - xp);
		// }
		// if (rotate_x > 0 && distv > distn)
		// {			
		// 	printf("2\n");
		// 	xp1 = (int)((float)((float)x + kef[0] )/m[0]);
		// 	xp = (int)((float)((float)x + kef[1] )/m[1]);
		// 	xpdx = (xp1 - xp);
		// }
		// if  (rotate_x < 0 && distv > distn)
		// {
		// 	printf("3\n");
		// 	xp = (int)((float)((float)x + kef[0] )/m[0]);
		// 	xp1 = (int)((float)((float)x + kef[1] )/m[1]);
		// 	xpdx = (xp1 - xp);
		// }
		// if  (rotate_x < 0 && distv < distn)
		// {
		// 	printf("4\n");
		// 	xp1 = (int)((float)((float)x + kef[0] )/m[0]);
		// 	xp = (int)((float)((float)x + kef[1] )/m[1]);
		// 	xpdx = (xp1 - xp);
		// }
		// if (distn == 0|| distv == 0)
		// {
			
		// }
		// printf ("%d \n", xp1);
		brez (stena1_x[x], stena2_x[x], stena1_y[x], stena2_y[x], image, xp,  start, p, offset, xpdx);
		x++;
	}
	i = 0;
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
}
