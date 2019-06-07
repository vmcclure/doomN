#include "doom.h"

void brez2(float x0, float x1, float y0, float y1, t_tga image,  float xp, int start, uint32_t *p, double *offloor)
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

	if (x0 > 810 && x1 > 810)
		return ;
	e = -1;
	dx = fabs(x1 - x0);
	dy = fabs(y1 - y0);
	// printf ("%d \n", start);
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
	
	// if ((start == 1 && y >= 800))
	// {
		
	// 	dir = (atan((float)(dy)/(float)(dx)));
	// 	xt = ((y - 800) / sin(dir)) * cos(dir) + x;
	// 	dist =  pow(pow(xt - x, 2) + pow(800 - y, 2), 0.5);//y - 800.0;//
	// 	x = x + dist * cos(dir) * e ;
	// 	y = y - dist * sin(dir);
	// 	// y = 799;
	// }
	// if ((start == 2 && y < 0))
	// {
	// 	dir = (atan((float)(dy)/(float)(dx)));
	// 	xt = ((fabsf(y)) / sin(dir)) * cos(dir) + x;
	// 	dist =  pow(pow(xt - x, 2) + pow(y, 2), 0.5);
	// 	x = x + dist * cos(dir) * e;
	// 	y = y + dist * sin(dir);
	// 	// y = 0;
	// }
	dist = pow(pow(dx, 2) + pow(dy, 2), 0.5);
	while (y <= y0 && y >= y1)
	{
		if ((start == 2 && y >= 800) || (start == 1 && y < 0))
            break ;
		if ((start == 1 && y >= 800))
			y = 800;
		if ((start == 2 && y < 0))
			y = 0;
		y += ey; ;
		if (d < 0)
			d +=d1;
		else
		{
			x += e;			
			d +=d2;
		}
		//xp = xp + xp1;
		
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

void	drawfloor1(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor, t_fvector	*fl, float *offloorright, float *offloorleft, float *topleft, float *topright)
{
	float	endy;
	float	y;
	float		x;
	int		i;
	float m;
	float k;
	int xp;
	int yp;
	int startxp;
	float dy;
	int startyp;
	float dx;
	int r;
	int g;
	int b;
	float kef;
	float maxdist;
	float mindist;
		float *stena1_x;
	float *stena1_y;
	float *stena2_x;
	float *stena2_y;
	int start;
	float dx1;
	float dir1;
	float xt;
	float dir4;
	float dir;
	float dirx;
	float diry;
	float shag_dlya_1_steni;
	float shag_dlya_2_steni;
	float nizx[800];
	float nizy[800];
	float verhxtext[800];
	float verhytext[800];
	float verhx[800];
	float verhy[800];
	int mask[4];
	float dxtext;
	float dytext;
	int e;
	e = 1;
	float dist;
	t_tga *image;
	image = tgafloor;
	if (wa.p[0].x > wa.p[1].x)
		ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	x = wa.p[0].x;
	i = 0;
	dx = fabsf(offloorright[0] - offloorleft[0]);
	dy = fabsf(offloorright[1] - offloorleft[1]);
	// printf("%f %f %f %f %f\n", topleft[0], topleft[1], topright[0], topright[1], dx);
	dx = dx / 799.0;
	dy = dy / 799.0;
	// printf(" %f \n", dx);
	// dir = (atan(dy/dx));
	while (i < 800)
	{
		nizx[i] = offloorleft[0] + (float)i * dx;
		nizy[i] = offloorleft[1] + (float)i * dy;		
		i++;
	}
	printf("\n");
	// printf("%f %f %f %f\n\n", fl[0].y, fl[1].y, fl[2].y, fl[3].y);
	i = 0;
	dx = fabsf(fl[1].x - fl[0].x);
	dy = fabsf(fl[1].y - fl[0].y);
	dy = dy/dx;
	while (i < fl[1].x)
	{
		verhx[i] = i;
		verhy[i] = fl[0].y -  ((float)i * dy );
		
		i++;
	}
	k = 0;
	dx = fabsf(fl[1].x - fl[2].x);
	dy = fabsf(fl[1].y - fl[2].y);
	dy = dy/dx;
	while (i < fl[2].x)
	{
		verhx[i] = i;
		verhy[i] = fl[1].y -  ((float)k * dy );
		
		i++;
		k ++;
	}
	dx = fabsf(fl[2].x - fl[3].x);
	dy = fabsf(fl[2].y - fl[3].y);
	dy = dy/dx;
	k = 0;
	while (i < fl[3].x)
	{
		verhx[i] = i;
		verhy[i] = fl[2].y + ((float)k * dy );
		
		i++;
		k++;
		
	}
	// printf("%d %f %f %f %f\n", i, fl[2].y, dy, verhy[i-1], fl[3].y);
	i = 0;
	

	dx = fabsf(fl[0].x - fl[1].x);
	dy = (1.0 - topleft[1])/dx;
	k = 0;
	while(i < fl[1].x)
	{
		verhxtext[i] = topleft[0];
		verhytext[i] = topleft[1] + dy * (float)k;
		
		i++;
		k++;
		
	}
	
	// printf("%f %f %f %f %f\n", topleft[0], topleft[1], topright[0], topright[1], verhytext[i-1]);
	k = 0;
	dx = fabsf(fl[1].x - fl[2].x);
	dx = 1.0 / dx;
	while (i < fl[2].x)
	{
		verhxtext[i] = dx *k;//topleft[0];
		verhytext[i] = 1;//topleft[1] + dy * (float)k;
		
		i++;
		k++;
	}
	k = 0;
	dx = fabsf(fl[2].x - fl[3].x);
	dy = (1-topright[1])/dx;
	while (i < fl[3].x)
	{
		verhxtext[i] = topright[0];
		verhytext[i] = 1 - (dy * (float)k);
				// printf("%f %f\n", verhxtext[i], verhytext[i]);
		i++;

		k++;
	}

	x = 0;
	while(x < 800)
	{
		y = verhy[(int)x];
		dy = (800.0 -verhy[(int)x]);
		dxtext = verhxtext[(int)x] - nizx[(int)x];
		dxtext = dxtext/dy;
		
		dytext = verhytext[(int)x] - nizy[(int)x];
		
		dytext = dytext/dy;

		
		while (y < 800)
		{
			yp =(int)((image->height -1)* (verhytext[(int)x] - (y - verhy[(int)x]) * dytext));
			xp = (int)((image->width - 1) * (verhxtext[(int)x] - (y - verhy[(int)x]) * dxtext));
					// printf("%d \n ", xp);
			xp = xp ;//% image->width);
			yp = yp;// % image->height;
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
				printf("%d %d\n", xp, yp);
			}
			// a = image->pic[yp][(int)xp].alpha;
			y++;
			
			p[(int)x + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
		}
		x++;
	}
	// printf("\n");
	i = 0;
	// printf("\n");
	// dy = fl[0].y;
	// if (fl[0].y < 800)
	// {
	// 	dx = fl[0].x - fl[1].x;
	// 	dy = fl[0].y - fl[1].y;
	// 	// printf("tyt %f %f %f %f\n", fl[0].y, fl[0].x, dx, dy);
	// 	dir = (atan((float)(dy)/(float)(dx)));
	// 	xt = ((fl[0].y - 800) / sin(dir)) * cos(dir) + fl[0].x;
	// 	dist =  pow(pow(xt - fl[0].x, 2) + pow(800 - fl[0].y, 2), 0.5);//y - 800.0;//
	// 	fl[0].x = fl[0].x - dist * cos(dir) ;
	// 	fl[0].y = fl[0].y - dist * sin(dir);
	// 	// printf("tyt %f %f\n", fl[0].y,  fl[0].x);
	// }
	// if (fl[3].y < 800)
	// {
	// 	dx = fl[2].x - fl[3].x;
	// 	dy = fl[3].y - fl[2].y;
	// 	// printf("tyt %f %f %f %f\n", fl[3].y,  fl[3].x, fl[2].y, fl[2].x);
	// 	// printf("tyt %f %f\n", fl[3].y, fl[3].x);
	// 	dir = (atan((float)(dy)/(float)(dx)));
	// 	xt = ((fl[3].y - 800) / sin(dir)) * cos(dir) + fl[3].x;
	// 	dist =  pow(pow(xt - fl[3].x, 2) + pow(800 - fl[3].y, 2), 0.5);//y - 800.0;//
	// 	fl[3].x = fl[3].x + dist * cos(dir);
	// 	fl[3].y = fl[3].y - dist * sin(dir);
	// 	// printf("tyt %f %f\n", fl[2].y,  fl[2].x);
	// 	// printf("tyt %f %f\n\n", fl[3].y,  fl[3].x);
	// }
	// //  printf("%f %f %f %f\n", fl[0].x,  fl[1].x, fl[2].x, fl[3].x);
	 
	// dx = fl[2].x - fl[1].x;
	// dx1 = fl[3].x - fl[0].x;
	// if (dx > dx1)
	// {
	// 	maxdist = dx;
	// 	mindist = dx1;
	// 	start = 2;
	// 	shag_dlya_1_steni = (float)mindist / (float)maxdist;
	// 	shag_dlya_2_steni = 1.0;
	// }
	// else
	// {
	// 	start = 1;
	// 	maxdist = dx1;
	// 	mindist = dx;
	// 	shag_dlya_1_steni = 1.0;
	// 	shag_dlya_2_steni = (float)mindist / (float)maxdist;
	// }
	// stena1_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	// stena1_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	// stena2_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	// stena2_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	// while (i < maxdist)
	// {
	// 	stena1_x[(int)i] = fl[0].x  + (i * shag_dlya_1_steni);
	// 	stena1_y[(int)i] = fl[0].y/(1.0- offloor[0]) ;//+ (i * shag_dlya_1_steni );
	// 	stena2_x[(int)i] = fl[1].x + (i * shag_dlya_2_steni);
	// 	stena2_y[(int)i] = fl[1].y;
	// 	if (stena1_x[(int)i] < 0 && stena2_x[(int)i] < 0)
	// 		x = i;
	// 	i++;
	// }
	// x = 0;
	// m = ((float)maxdist) / (float)(image->width);
	// while (x < maxdist)
	// {
	// 	xp = x / m;
	// 	brez2 (stena1_x[(int)x], stena2_x[(int)x], stena1_y[(int)x], stena2_y[(int)x], *image, xp,  start, p,  offloor);
	// 	x++;
	// }
	
}
