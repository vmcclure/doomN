/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quitprogram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:07:47 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/24 15:41:46 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			quitprogram(t_doom *doom)
{
	destrotwindow(doom);
	ft_memdel((void**)&doom);
	SDL_Quit();
}
