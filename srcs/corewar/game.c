/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:40:57 by thzimmer          #+#    #+#             */
/*   Updated: 2019/09/11 16:23:16 by thzimmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "curses.h"

/*
** Read the current operation code.
*/

static void	read_op_code(t_proc *cur, t_game *game)
{
	cur->op_code = game->arena[cur->pc];
	if (cur->op_code > 0 && cur->op_code < 17)
		cur->cycles_to_wait = game->op_tab[(int)cur->op_code].cycles - 1;
	else
		cur->op_code = 0;
}

/*
** Run the operation.
*/

static void	execute_op(t_proc *cur, t_game *game)
{
	if (!cur->op_code)
		cur->pc = MODM(cur->pc + 1);
	else
		game->exec_op[(int)cur->op_code](cur, game);
}

/*
** Run the procedure.
*/

static void	run_proc(t_proc *cur, t_game *game)
{
	if (game->viewer_mod)
		viewer_buttons(game);
	if (cur->cycles_to_wait)
		cur->cycles_to_wait--;
	else
		read_op_code(cur, game);
	if (!(cur->jump = 0) && !cur->cycles_to_wait)
		execute_op(cur, game);
}

/*
** Update the game info at the end of the round.
*/

static void	update_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->nb_players)
	{
		if (!game->player[i].lives)
			game->player[i].alive = 0;
		game->player[i].lives = 0;
	}
	if (game->nb_lives > NBR_LIVE && !(game->nb_check = 0))
		game->cycle_to_die -= CYCLE_DELTA;
	else
	{
		if (++game->nb_check == MAX_CHECKS && !(game->nb_check = 0))
			game->cycle_to_die -= CYCLE_DELTA;
	}
	if (game->cycle_to_die <= 0)
		game->running = 0;
	game->nb_lives = 0;
	kill_proc(game);
}

/*
** Main game loop.
*/

void		corewar(t_game *game)
{
	t_proc	*cur;

	while (game->running && !(game->cycle = 0))
	{
		while (++game->cycle <= game->cycle_to_die && (cur = game->proc))
		{
			game->viewer_mod ? usleep(game->viewer.sleep) : 0;
			if (game->dump && game->tot_cycle == game->dump)
			{
				game->running = 0;
				break ;
			}
			game->tot_cycle++;
			while (cur)
			{
				game->viewer.cursor[cur->pc] = cur->id + 6;
				run_proc(cur, game);
				cur = cur->next;
			}
			game->viewer_mod ? print_viewer(game) : 0;
		}
		if (game->running)
			update_game(game);
	}
	free_proc(game);
}
