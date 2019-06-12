#include "doom.h"

void brez2(float x0, float x1, float y0, float y1, t_tga image,  float xp, float start, uint32_t *p, float offloor)
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
	float yp;
	float k;
	float m;
	int i;
	float e;
	char a;
	float ey;
	float dir;
	float dist;

	// if (x0 > 810 && x1 > 810)
	// 	return ;
	e = 1;
	dx = (x0 - x1);
	if (dx < 0)
		e = -1;
	dy = (y0 - y1);
	dir = atan(dy/dx);
	// printf ("%d \n", start);
	x = x0;
	r = 255;
	g = 0;
	b = 0;
	y = y0;
	yp = start;

	dist = pow(pow(dx, 2) + pow(dy, 2), 0.5);
	// printf("%f\n", dist);
	i= 0;
	while (i < dist)
	{
		x = x - cos(dir) * e;
		y = y - sin(dir) * e;
		
		xp = (int)xp % image.width;
		yp =  (yp + offloor);

		r = image.pic[(int)(yp * (float)image.height)% image.height][(int)xp].red;
		g = image.pic[(int)(yp* (float)image.height)% image.height][(int)xp].green;
		b = image.pic[(int)(yp* (float)image.height)% image.height][(int)xp].blue;
		if (y > 0 && y < 800 && x > 0 && x < 800)
			p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
		// else
		// 	printf ("%f\n", y);
		i++;
	}
	x = x1;
	r = 255;
	g = 0;
	b = 0;
	y = y1;
	// while (x < x0)
	// {
	// 	x = x + cos(dir);
	// 	y = y - sin(dir);
		
	// 	xp = (int)xp % image.width;
	// 	yp =  (yp + offloor);

	// 	r = image.pic[(int)(yp * (float)image.height)% image.height][(int)xp].red;
	// 	g = image.pic[(int)(yp* (float)image.height)% image.height][(int)xp].green;
	// 	b = image.pic[(int)(yp* (float)image.height)% image.height][(int)xp].blue;
	// 	if (y > 0 && y < 800 && x > 0 && x < 800)
	// 		p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
	// 	// else
	// 	// 	printf ("%f\n", y);
	// 	i++;
	// }
	d = 2* (dx - dy);
	start = 2;
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
	// while (y <= y0 && y >= y1)
	// {
	// 	// if ((start == 2 && y >= 800) || (start == 1 && y < 0))
    //     //     break ;
	// 	// if ((start == 1 && y >= 800))
	// 	// 	y = 800;
	// 	// if ((start == 2 && y < 0))
	// 	// 	y = 0;
	// 	y += ey; ;
	// 	if (d < 0)
	// 		d +=d1;
	// 	else
	// 	{
	// 		x += e;			
	// 		d +=d2;
	// 	}
	// 	//xp = xp + xp1;
		
	// 	// yp =(int)((y - y1)/k);
	// 	// if (yp >= 0 && yp < image.height && xp >= 0 && xp < image.width)
	// 	{
	// 		r = 255;//image.pic[yp][(int)xp].red;
	// 		g = 0;//image.pic[yp][(int)xp].green;
	// 		b = 0;//image.pic[yp][(int)xp].blue;
	// 		// a = 255;//image.pic[yp][(int)xp].alpha;
	// 	}
	// 	// if (x >= 0 && x < 800 && y >= 0 && y < 800)
	// 	{
	// 		// if (a != 0)
	// 		{
	// 			if (y < y0 && y > y1 && x > 0 && x < 799)
	// 				p[(int)(x+1) + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
	// 				p[(int)x + ((int)y * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
	// 		}
	// 	}
	// 	// SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	// 	// 	SDL_RenderDrawPoint (renderer,x, y);
	// }
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
	float start;
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
	float *verhtextx;
	float *verhtexty;
	float *verhx;
	float *verhy;
	int mask[4];
	float dxtext;
	float dytext;
	float *niztextx;
	float *niztexty;
	float *nizposx;
	float *nizposy;
	int delta;
	int f;
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
	// printf("%f %f %f %f \n", fl[0].y, fl[1].y, fl[2].y, fl[3].y);
	dx = dx / 799.0;
	dy = dy / 799.0;
	delta = 800 - fl[3].y + 800 + 800 - fl[0].y;
	// printf(" %d \n", delta);
	// dir = (atan(dy/dx));
	nizposx = (float *)malloc((sizeof(float)) * (delta+1));
	nizposy = (float *)malloc((sizeof(float)) * (delta+1));
	niztextx = (float *)malloc((sizeof(float)) * (delta+1));
	niztexty = (float *)malloc((sizeof(float)) * (delta+1));
	verhx = (float *)malloc((sizeof(float)) * (delta+1));
	verhy = (float *)malloc((sizeof(float)) * (delta+1));
	verhtextx = (float *)malloc((sizeof(float)) * (delta+1));
	verhtexty = (float *)malloc((sizeof(float)) * (delta+1));
	dist = 800 - fl[0].y;
	dx = topleft[0] - offloorleft[0];
	dy = topleft[1] - offloorleft[1];
	dx = dx/dist;
	dy = dy/dist;
	i = fl[0].y;
	k = 0;
	while (i < 800)
	{

		nizposx[(int)k] = 0;
		nizposy[(int)k] = i;
		niztextx[(int)k] = topleft[0]  - dx * k;
		niztexty[(int)k] = topleft[1] - dy * k;
		// printf(" %f %f\n", niztexty[(int)k], niztextx[(int)k]);
		i++;
		k++;
	}
	i = 0;
	dx = offloorright[0] - offloorleft[0];
	dy = offloorright[1] - offloorleft[1];
	// printf("%f %f \n", dx , dy);
	dx = dx / 799.0;
	dy = dy / 799.0;
	while (i < 800)
	{

		nizposx[(int)k] = i;
		nizposy[(int)k] = 799;
		niztextx[(int)k] = offloorleft[0] + dx * i;
		niztexty[(int)k] = offloorleft[1] + dy * i;
		
		k++;
		i++;
		
	}
	i = 799;
	dx = topright[0] - offloorright[0];
	dy = topright[1] - offloorright[1];
	dist = 800 - fl[3].y;
	dx = dx / dist;
	dy = dy/ dist;
	f = 0;
	while (i > fl[3].y)
	{
		nizposx[(int)k] = 799;
		nizposy[(int)k] = i;
		niztextx[(int)k] = offloorright[0] + f * dx;
		niztexty[(int)k] = offloorright[1] + f * dy;
		// printf(" %f %f\n", niztexty[(int)k], niztextx[(int)k]);
		i--;
		k++;
		f++;
	}
	// printf("\n");
	i = 0;
	dx = fl[2].x - fl[1].x;
	dy = fl[2].y - fl[1].y;
	dx = dx/delta;
	dy = dy/delta;
	dist = 1.0 / delta;
	while (i < delta)
	{
		verhx[i] = fl[1].x + dx * i;
		verhy[i] = fl[1].y + dy * i;
		verhtextx[i] = i * dist;
		verhtexty[i] = 1;
		// printf ("%f\n",verhtextx[i]);
		i++;

	}
	i = 0;
	x = 0;
	while (x < delta)
	{
		dx = nizposx[(int)x] - verhx[(int)x];
		dy = nizposy[(int)x] - verhy[(int)x];
		dist = pow(pow(dx, 2) + pow(dy, 2), 0.5);
		dy = verhtexty[(int)x] - niztexty[(int)x];
		dy = dy / dist;
		// if (x == 1)
		// printf("%f\n", dy);
		
		
		// offloor = dy;
		start = niztexty[(int)x];
		// dist = pow(pow(verhx[x] - nizposx[x], 2) +  pow(verhy[x] - nizposy[x], 2), 0.5)
		// if (x > 500)
		// 	printf("%f %f\n", nizposx[(int)x],  nizposy[(int)x]);
		// 
		xp = image->height * verhtextx[(int)x];
		brez2(nizposx[(int)x], verhx[(int)x], nizposy[(int)x], verhy[(int)x], *image, xp,  start, p,  dy);
		x++;
	}



	
	// if (wa.p[0].x > wa.p[1].x)
	// 	ft_swap((void**)&wa.p[0], (void**)&wa.p[1]);
	// x = wa.p[0].x;
	// i = 0;
	// dx = fabsf(offloorright[0] - offloorleft[0]);
	// dy = fabsf(offloorright[1] - offloorleft[1]);
	// // printf("%f %f %f %f %f\n", topleft[0], topleft[1], topright[0], topright[1], dx);
	// dx = dx / 799.0;
	// dy = dy / 799.0;
	// // printf(" %f \n", dx);
	// // dir = (atan(dy/dx));
	// while (i < 800)
	// {
	// 	nizx[i] = offloorleft[0] + (float)i * dx;
	// 	nizy[i] = offloorleft[1] + (float)i * dy;		
	// 	i++;
	// }
	// printf("\n");
	// // printf("%f %f %f %f\n\n", fl[0].y, fl[1].y, fl[2].y, fl[3].y);
	// i = 0;
	// dx = fabsf(fl[1].x - fl[0].x);
	// dy = fabsf(fl[1].y - fl[0].y);
	// dy = dy/dx;
	// while (i < fl[1].x)
	// {
	// 	verhx[i] = i;
	// 	verhy[i] = fl[0].y -  ((float)i * dy );
		
	// 	i++;
	// }
	// k = 0;
	// dx = fabsf(fl[1].x - fl[2].x);
	// dy = fabsf(fl[1].y - fl[2].y);
	// dy = dy/dx;
	// while (i < fl[2].x)
	// {
	// 	verhx[i] = i;
	// 	verhy[i] = fl[1].y -  ((float)k * dy );
		
	// 	i++;
	// 	k ++;
	// }
	// dx = fabsf(fl[2].x - fl[3].x);
	// dy = fabsf(fl[2].y - fl[3].y);
	// dy = dy/dx;
	// k = 0;
	// while (i < fl[3].x)
	// {
	// 	verhx[i] = i;
	// 	verhy[i] = fl[2].y + ((float)k * dy );		
	// 	i++;
	// 	k++;		
	// }
	// // printf("%d %f %f %f %f\n", i, fl[2].y, dy, verhy[i-1], fl[3].y);
	// i = 0;
	

	// dx = fabsf(fl[0].x - fl[1].x);
	// dy = (1.0 - topleft[1])/dx;
	// k = 0;
	// while(i < fl[1].x)
	// {
	// 	verhxtext[i] = topleft[0];
	// 	verhytext[i] = topleft[1] + dy * k;		
	// 	i++;
	// 	k++;		
	// }
	
	// // printf("%f %f %f %f %f\n", topleft[0], topleft[1], topright[0], topright[1], verhytext[i-1]);
	// k = 0;
	// dx = fabsf(fl[1].x - fl[2].x);
	// dx = 1.0 / dx;
	// while (i < fl[2].x)
	// {
	// 	verhxtext[i] = dx *k;//topleft[0];
	// 	verhytext[i] = 1;//topleft[1] + dy * (float)k;
		
	// 	i++;
	// 	k++;
	// }
	// k = 0;
	// dx = fabsf(fl[2].x - fl[3].x);
	// dy = (1-topright[1])/dx;
	// while (i < fl[3].x)
	// {
	// 	verhxtext[i] = topright[0];
	// 	verhytext[i] = 1 - (dy * (float)k);
	// 			// printf("%f %f\n", verhxtext[i], verhytext[i]);
	// 	i++;

	// 	k++;
	// }
	// i = 0;
	// // dx = 1.0 / 800;
	// // while (i < 800.0)
	// // {
	// // 	verhxtext[i] = (float)i * dx;
	// // 	verhytext[i] = 1.0;
	// // 	i++;
	// // }
	// x = 0;
	// while(x < 800)
	// {
	// 	y = verhy[(int)x];
	// 	dy = (800.0 -verhy[(int)x]);
	// 	dxtext = verhxtext[(int)x] - nizx[(int)x];
	// 	dxtext = dxtext/dy;
		
	// 	dytext = verhytext[(int)x] - nizy[(int)x];
		
	// 	dytext = dytext/dy;

		
	// 	while (y < 800)
	// 	{
	// 		yp =(int)((image->height -1)* (verhytext[(int)x] - (y - verhy[(int)x]) * dytext));
	// 		xp = (int)((image->width - 1) * (verhxtext[(int)x] - (y - verhy[(int)x]) * dxtext));
	// 				// printf("%d \n ", xp);
	// 		xp = xp ;//% image->width);
	// 		yp = yp;// % image->height;
	// 		if (xp < image->width && xp >= 0 && yp < image->height && yp >= 0 )
	// 		{
	// 			r = image->pic[yp][(int)xp].red;
	// 			g = image->pic[yp][(int)xp].green;
	// 			b = image->pic[yp][(int)xp].blue;
	// 		}
	// 		else
	// 		{
	// 			r = 0;
	// 			g = 255;
	// 			b = 0;
	// 			// printf("%d %d\n", xp, yp);
	// 		}
	// 		// a = image->pic[yp][(int)xp].alpha;
	// 		y++;
			
	// 		p[(int)x + ((int)(y) * 800)] = ((((((255 << 8) | r) << 8) | g) << 8) | b);
	// 	}
	// 	x++;
	// }
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
	free(nizposx);
	free(nizposy);
	free(niztextx);
	free(niztexty);
	free(verhx);
	free(verhy);
	free(verhtextx);
	free(verhtexty);

	
}
