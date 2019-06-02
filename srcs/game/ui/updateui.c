/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 11:59:14 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 13:35:11 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		boxcollision(t_button button, t_ivector2d mousepos)
{
	if (mousepos.x > button.rect.start.x &&
	mousepos.y > button.rect.start.y &&
	mousepos.x < button.rect.start.x + button.rect.width &&
	mousepos.y < button.rect.start.y + button.rect.height)
		return (1);
	return (0);
}

void	updateui(t_doom *doom)
{
	if (doom->setting.input.mousekey[0])
	{
		if (boxcollision(doom->settingui.plussound, doom->setting.input.mousepos))
		{
			addsound(&doom->setting);
			printf("Pluse sound: %f\n", doom->setting.soundvolume);
		}
		if (boxcollision(doom->settingui.minussound, doom->setting.input.mousepos))
		{
			subsound(&doom->setting);
			printf("Minus sound: %f\n", doom->setting.soundvolume);
		}
		if (boxcollision(doom->settingui.plusmusic, doom->setting.input.mousepos))
		{
			addmusic(&doom->setting);
			printf("Plus music: %f\n", doom->setting.musicvolume);
		}
		if (boxcollision(doom->settingui.minusmusic, doom->setting.input.mousepos))
		{
			submusic(&doom->setting);
			printf("Minus music: %f\n", doom->setting.musicvolume);
		}
	}
}
