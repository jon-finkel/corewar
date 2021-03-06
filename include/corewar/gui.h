/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar/gui.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/31 18:54:09 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_GUI_H
# define COREWAR_GUI_H

# include <libft.h>
# include <ncurses.h>

# include "proc.h"

# define GUI_COLOR_DFT 0
# define GUI_COLOR_HINT (GUI_COLOR_DFT + 5)
# define GUI_COLOR_INV (GUI_COLOR_HINT + 5)

# define GUI_INV (1 << 0)
# define GUI_NOCOLOR (1 << 1)
# define GUI_BOLD (1 << 2)
# define GUI_HINT (1 << 3)

/*
** TODO: Doc
** @return
*/
int		vm_guiinit(void);

/*
** TODO: Doc
** @return
*/
int		vm_guiupdate(void);

/*
** TODO: Doc
** @return
*/
void	vm_guiproc(t_proc *proc);

/*
** TODO: Doc
** @return
*/
void	vm_guimarkdead(t_proc *proc);

/*
** TODO: Doc
** @return
*/
void	vm_guiwinner(t_player *player);

/*
** TODO: Doc
** @param i
** @param c
** @param val
** @return
*/
int		vm_guinotify(uint16_t i, int color, int attrs, uint8_t lt);

/*
** TODO: Doc
** @return
*/
int		vm_guiexit(void);

#endif
