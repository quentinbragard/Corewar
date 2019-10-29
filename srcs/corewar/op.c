/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:08:42 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 18:08:44 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Structure containing operations description.
*/

t_op		g_op_tab[17] =
{
	{{0}, 0, {0}, 0, 0, {0}, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};

/*
** Save the operations description in the game structure.
*/

void		set_op_tab(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 17)
		game->op_tab[i] = g_op_tab[i];
}

/*
** Save the 16 operations in the game structure.
*/

void		get_functions(t_game *game)
{
	game->exec_op[0] = NULL;
	game->exec_op[1] = op_live;
	game->exec_op[2] = op_ld;
	game->exec_op[3] = op_st;
	game->exec_op[4] = op_add;
	game->exec_op[5] = op_sub;
	game->exec_op[6] = op_and;
	game->exec_op[7] = op_or;
	game->exec_op[8] = op_xor;
	game->exec_op[9] = op_zjmp;
	game->exec_op[10] = op_ldi;
	game->exec_op[11] = op_sti;
	game->exec_op[12] = op_fork;
	game->exec_op[13] = op_lld;
	game->exec_op[14] = op_lldi;
	game->exec_op[15] = op_lfork;
	game->exec_op[16] = op_aff;
}

/*
** Live operation : For player n° [DIR].
*/

void		op_live(t_proc *proc, t_game *game)
{
	int	nbr;
	int i;

	i = -1;
	nbr = get_int(game->arena, MODM(proc->pc + 1));
	if (nbr > 0 && nbr <= game->nb_players)
	{
		game->player[nbr - 1].lives++;
		game->player[nbr - 1].alive = 1;
		game->last_alive = nbr;
		game->nb_lives++;
		proc->alive = 1;
		while (++i < 5)
			game->viewer.bold[MODM(proc->pc + i)] = 200;
	}
	proc->pc = MODM(proc->pc + 5);
}

/*
** Load operation : Load [DIR | IND] -> [REG].
*/

void		op_ld(t_proc *proc, t_game *game)
{
	int jump;
	int	val;
	int reg;

	if (!coding_byte(game->arena[MODM(proc->pc + 1)], \
		game->op_tab[2].params_type, 0, &jump) && !(jump = 0))
	{
		proc->jump = 2;
		val = get_param(game, proc, \
			((game->arena[MODM(proc->pc + 1)]) >> 6) & 3, 0);
		reg = game->arena[MODM(proc->pc + proc->jump)] - 1;
		if (reg >= 0 && reg <= REG_NUMBER - 1)
		{
			proc->reg[reg] = val;
			proc->carry = val ? 0 : 1;
		}
		proc->jump++;
	}
	proc->pc = MODM(proc->pc + jump + proc->jump);
}
