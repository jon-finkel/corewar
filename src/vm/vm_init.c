/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:10:16 by lfabbro           #+#    #+#             */
/*   Updated: 2018/03/14 16:35:40 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

t_proc		*cw_vm_parse(uint8_t *mem, const char *filename, uint16_t color)
{
	int				fd;
	ssize_t			bin_size;
	char			buf[4096];
	t_proc			*proc;

	proc = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		cw_exit(3, "Failed opening file.\n");
	if (read(fd, &buf, _CW_HEAD_SZ) < _CW_HEAD_SZ)
		cw_exit(3, "Failed reading file header.\n");
	if (*(unsigned int*)buf != _CW_MAGIC)
		cw_exit(3, "Wrong file: magic number.\n");
	if ((bin_size = read(fd, &buf, CHAMP_MAX_SIZE + 1)) <= 0)
		cw_exit(3, "Failed reading file binary.\n");
	if (bin_size > CHAMP_MAX_SIZE)
		cw_exit(3, "Champion exceeding size: %d\n", bin_size);
	proc = malloc(sizeof(t_proc));
	proc->color = color;
	proc->pc = mem;
	cw_mem_cpy(mem, (const uint8_t *)buf, (size_t)bin_size, proc->color);
	proc->wait = cw_instr_cycles(*(uint8_t*)mem);
	if (close(fd) < 0)
		cw_exit(3, "Failed closing fd.\n");
	return (proc);
}

int		cw_vm_init(int ac, char **av)
{
	int		i;
	int		plyrs_dist;
	int		dist;
	t_proc	*ptr;

	i = g_optind;
	plyrs_dist = MEM_SIZE / (ac - g_optind);
	dist = 0;
	cw_nc_init();
	g_cw->cycle_to_die = CYCLE_TO_DIE;
	while (i < ac && (i - g_optind) < MAX_PLAYERS)
	{
		ptr = cw_vm_parse(&(g_cw->mem[dist * plyrs_dist]), av[i], dist + 1);
		if (ptr == NULL)
			return (cw_exit(EXIT_FAILURE, "%s: Failed parsing file.\n", av[i]));
		ptr->next = g_cw->procs;
		if (g_cw->procs)
			g_cw->procs = ptr;
		++g_cw->proc_count;
		++dist;
		++i;
	}
	g_cw->prev = g_cw->procs;
	g_cw->current = g_cw->procs;
	return (EXIT_SUCCESS);
}
