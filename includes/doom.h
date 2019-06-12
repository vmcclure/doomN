/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:40:29 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 18:58:13 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "../lib/libft/includes/libft.h"
# include "../lib/ft_graphics/includes/vector.h"
# include "../lib/ft_graphics/includes/rect.h"
# include "../lib/ft_graphics/includes/rotate.h"
# include "../lib/ft_graphics/includes/mat.h"
# include "../lib/ft_graphics/includes/utils.h"
# include "../lib/ft_graphics/includes/color.h"
# include "../lib/TGA-Reader/include/tga.h"
# include "filesystem.h"
# include "physics.h"
# include <stdlib.h>

# ifdef __APPLE__
#  define CREATEFLAG S_IWRITE | S_IREAD
#  include "../lib/SDL/include/SDL2/SDL.h"
#  include "../lib/SDL/include/SDL2/SDL_mixer.h"
# elif __linux__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_mixer.h>
# elif __WIN32__
#  define CREATEFLAG __S_IWRITE | __S_IREAD
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL.h>
#  include <C:\MinGW\msys\1.0\include\SDL2\SDL_mixer.h>
# endif

typedef struct	s_camera
{
	float		near;
	float		far;
	float		fov;
	float		aspectratio;
}				t_camera;

typedef struct	s_window
{
	SDL_Window		*window;
	t_ivector2d		size;
	SDL_Texture		*texture;
	uint32_t		*pixels;
	SDL_Renderer	*renderer;
	int				state;
}				t_window;
t_window		*createwindow(t_ivector2d size, char *title, Uint32 flag);

typedef struct	s_bar
{
	t_rgba		color;
	t_fvector2d	pos;
	t_fvector2d	widthheight;
}				t_bar;
t_bar		setbar(t_rgba color, t_fvector2d pos, t_fvector2d wh);
void		drawbar(uint32_t *p, t_bar bar);

typedef struct	s_anim
{
	t_tga		*frame;
	t_tga		thisframe;
	int			maxframe;
	int			countframe;
	int			state;
}				t_anim;
t_anim			setanim(t_tga *frame, int maxframe);
void			startanim(t_anim *anim);
void			stopanim(t_anim *anim);
void			pauseanim(t_anim *anim);
void			unpauseanim(t_anim *anim);
void			nextframe(t_anim *anim);
void			previousframe(t_anim *anim);

typedef struct	s_mouse
{
	t_ivector2d	old;
	t_ivector2d	mousepos;
	float		sensivety;
}				t_mouse;

typedef struct	s_input
{
	t_mouse		mouse;
	const Uint8	*keystate;
	int			moveforward;
	int			movebackward;
	int			moveleft;
	int			moveright;
	int			rotleft;
	int			rotright;
	int			rotup;
	int			rotdown;
	int			jump;
	t_ivector2d	mousepos;
	int			mousekey[3];
}				t_input;

typedef struct	s_player
{
	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;
	size_t		sector;

	size_t		targetid;

	float		height;
	float		maxhealth;
	float		health;
	float		maxstamina;
	float		stamina;

	float		maxheightjump;
	float		movespeed;
	float		runspeed;

	int			run;
	int			jump;
}				t_player;

typedef enum	e_typeobj
{
	PLAYER,
	DECORE,
	ENEMY
}				t_typeobj;

typedef struct	s_object
{
	t_typeobj	typeobject;
	size_t		sector;

	t_fvector	pos;
	t_fvector	rotate;
	t_fvector	velosity;

	float		width;

	int			health;
	float		maxhealth;

	int			ismoveble;
	float		movespeed;

	int			isagression;
	int			agressionarea;

	size_t		texture;
}				t_object;

typedef struct	s_sector
{
	size_t			start;
	size_t			count;
	int				floor;
	int				height;
	int				type;
	size_t			walltexture;
}				t_sector;

typedef struct	s_map
{
	t_sector	*sectors;
	size_t		sectorcount;
	t_fvector	*walls;
	size_t		wallcount;

	t_object	*obj;
	size_t		objcount;

	t_player	startplayer;
}				t_map;

void		moveenemy(t_player play, t_map *map, t_object *obj, float delta);
void		agressionememy(t_player *player, t_object *obj);
void		damageenemy(t_player *player, t_object *obj, double delta);

typedef struct	s_wall
{
	t_fvector	p[4];
	float		offset[4];
}				t_wall;

typedef struct	s_setting
{
	t_input		input;
	t_ivector2d	resolution;
	float		soundvolume;
	float		musicvolume;
}				t_setting;

typedef struct	s_button
{
	t_tga		texture;
	t_irect		rect;
}				t_button;

typedef struct	s_settingui
{
	t_button	plussound;
	t_button	minussound;
	t_button	plusmusic;
	t_button	minusmusic;
}				t_settingui;

typedef struct	s_floor
{
	float		dx;
	float		dy;
	t_wall		wa;
	t_fvector2d min;
	t_fvector2d max;
	float		offloorright[2];
	float		offloorleft[2];
	float		topleft[2];
	float		topright[2];
	t_fvector 	a;
	t_fvector	b;
	size_t		floor;
}				t_floor;

typedef struct	s_doom
{
	char		*path;
	t_window	*win;
	SDL_Event	event;

	Uint64		lastframe;
	Uint64		currentframe;
	double		delta;

	t_setting	setting;
	t_settingui	settingui;

	t_tga		*texture;
	size_t		texturecount;
	t_tga		*font;

	t_player	player;

	t_map		*maps;
	size_t		mapcount;
	size_t		level;
	t_map		thismap;
}				t_doom;

typedef struct	s_dot
{
	t_ivector2d verh[800];
    t_ivector2d niz[800];
    t_ivector2d verhtext[800];
    t_ivector2d niztext[800];
}				t_dot;

t_tga		*tga;
t_tga		*tgafloor;
t_tga		*tgaenemy;

int			switchcordwall(t_fvector *p1, t_fvector *p2, float *offset, t_fvector2d angle);
void		initsettingui(t_doom *doom);
void		initsetting(t_setting *s);
void		calculate_floor(t_player play,t_fvector *w, uint32_t *p, t_tga texture, size_t count, size_t floor);
void		drawpoint(uint32_t *p, t_ivector2d size, t_ivector2d cord, t_rgba color);
void		drawrect(t_doom *doom, t_irect rect, t_rgba color);
void		drawline(uint32_t *p, t_fvector start, t_fvector end, t_rgb color);
void		drawsector(uint32_t *p, t_player play, t_fvector *w, size_t count);
void		drow_wall(uint32_t *p, t_wall wall, t_tga image, float *offset, float rotate_x);
void		drawfloor(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor, t_fvector	*fl);
void		drawfloor1(uint32_t *p, t_wall wa, t_rgb color, t_player player, double *offloor, t_fvector	*fl, float *offloorright, float *offloorleft, float *topleft, float *topright);  
void		drawceil(uint32_t *p, t_wall wa, t_rgb color);
void		drow_floor(t_floor *for_floor, uint32_t *p);
void		drawobj(t_doom *doom, t_map map);

void		drawminimap(uint32_t *p, t_doom *doom, size_t sector, t_ivector2d cord);
void		drawoptionmenu(t_doom *doom);

void		addmusic(t_setting *s);
void		submusic(t_setting *s);
void		addsound(t_setting *s);
void		subsound(t_setting *s);

void		destrotwindow(t_doom *doom);

void		updateevent(t_doom *doom);
void		update(t_doom *doom, double delta);
void		updateui(t_doom *doom);
void		draw(t_doom *doom);
void		drawui(t_doom *doom);
void		quitprogram(t_doom *doom);

t_player	defaultplayerdata(void);
void		addstamina(t_player *p, float addvalue);
void		minusstamina(t_player *p, float minusvalue);

void		addhealth(t_player *p, float addvalue);
void		minushealth(t_player *p, float minusvalue);
void		playerdeath(t_player *p);

void		playermove(t_doom *doom, double delta);
void		playerjump(t_doom *doom, t_player *player);

void		loadinput(char *path, t_input *input);

int			collide(t_fvector2d pos, t_fvector2d newpos,
t_fvector *w, size_t count);
int			inside(t_fvector2d i, t_fvector *p, size_t size);
size_t		isinside(t_fvector2d pos, t_map	map, size_t	lastsecid);

void		loadassets(char *path, t_doom *doom);
t_map		loadmap(char *path);
void		switchlevel(t_doom *doom, size_t level);

t_mat4x4	matcam(t_player *player);
t_mat4x4	matprojection(t_camera cam);
t_camera	initcam(t_ivector2d sizewin);


int			clip(t_player *player, t_fvector p[4], float offset[4], size_t c);

void		initdrawwall(t_fvector *view);
void		multmatrixdrawwall(t_fvector *view, t_mat4x4 mat);
void		wallproj(t_fvector *view, t_mat4x4 proj);
void		divdrawwall(t_fvector *view, float x, float y, float z);
void		adddrawwall(t_fvector *view, float x, float y, float z);
void		subdrawwall(t_fvector *view, float x, float y, float z);
void		multdrawwall(t_fvector *view, float x, float y, float z);

void		free2dstring(char **str);
size_t		stringcount(char **str);
void		error(const char *str);

#endif
