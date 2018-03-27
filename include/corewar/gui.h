/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/gui.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/26 17:15:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_GUI_H
# define COREWAR_GUI_H

# include <libft.h>
# include <ncurses.h>

# define CW_GUI_COLOR_DFT 1
# define CW_GUI_COLOR_HINT (CW_GUI_COLOR_DFT + 5)
# define CW_GUI_COLOR_INV (CW_GUI_COLOR_HINT + 5)

/*
** TODO: Doc
** @return 
*/
int	vm_guiinit(void);

/*
** TODO: Doc
** @return 
*/
int	vm_guiupdate(void);

/*
** TODO: Doc
** @param i 
** @param c 
** @param val 
** @return 
*/
int	vm_guinotify(uint16_t i, uint16_t c, uint8_t val);

/*
** TODO: Doc
** @return 
*/
int	vm_guiexit(void);

#endif
