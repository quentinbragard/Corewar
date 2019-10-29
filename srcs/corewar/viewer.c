/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:04:51 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/11 16:26:36 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "curses.h"

/*
** Initialize curses.
*/

void		init_curses(void)
{
	initscr();
	noecho();
	start_color();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	cbreak();
	init_color(COLOR_WHITE, 255, 255, 255);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GREEN);
	init_pair(8, COLOR_BLACK, COLOR_YELLOW);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_CYAN);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
}

/*
** Print the lives for each players.
*/

static void	print_lives(t_game *game)
{
	int	i;

	printw("\n%4cPLAYER%99c%14cLIVES%14c%15c", ' ', ' ', ' ', ' ', ' ');
	printw("PROCESSUS%14c%30c\n\n", ' ', ' ');
	i = -1;
	while (++i < game->nb_players)
	{
		attron(COLOR_PAIR(0));
		printw("    [%d] %-100s", i + 1, game->player[i].name);
		attroff(COLOR_PAIR(0));
		attron(COLOR_PAIR(i + 1));
		printw("%18d%36d\n", game->player[i].lives, game->player[i].nb_proc);
		if (game->player[i].alive)
			printw("         ALIVE");
		else
			printw("         DEAD");
		printw("\n");
		attroff(COLOR_PAIR(i + 1));
	}
	attron(COLOR_PAIR(game->last_alive));
	printw("\n    LAST PLAYER ALIVE : %s\n\n", \
		game->player[game->last_alive - 1].name);
	attroff(COLOR_PAIR(game->last_alive));
}

/*
** Print the stats of the game.
*/

static void	print_stats(t_game *game)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(0));
	print_lives(game);
	printw("\nCYCLE %12d    |    TOTAL NUMBER OF LIVES %25d / %-2d ", \
		game->tot_cycle, game->nb_lives, NBR_LIVE);
	printw("   |    CHECKS %24d / %-2d    |    CYCLES TO DIE %12d / %5d\n", \
		game->nb_check, MAX_CHECKS, game->cycle, game->cycle_to_die);
	printw("\n\nCONTROL PACE:    (DELAY = %d ms)\n", game->viewer.sleep / 1000);
	printw("\n  Delay up/down : <- / ->");
	printw("\n  Debug mod: SPACE (press again to cancel)\n\n\n");
	attroff(COLOR_PAIR(0));
	attroff(A_BOLD);
	refresh();
}

/*
** Parse input from stdin and modulate viewer speed.
*/

void		viewer_buttons(t_game *game)
{
	game->viewer.button = getch();
	if (game->viewer.button == KEY_LEFT)
		game->viewer.sleep += 10000;
	if (game->viewer.button == KEY_RIGHT)
		if (game->viewer.sleep >= 10000)
			game->viewer.sleep -= 10000;
	if (game->viewer.button == ' ')
	{
		if (game->viewer.sleep)
			game->viewer.sleep = 0;
		else
			game->viewer.sleep = 1000000;
	}
}

/*
** Print one cycle with curses.
*/

void		print_viewer(t_game *game)
{
	int i;

	i = -1;
	erase();
	while (++i < MEM_SIZE)
	{
		if (game->viewer.bold[i] > 0)
			attron(A_BOLD);
		attron(COLOR_PAIR(game->viewer.cursor[i] ? game->viewer.cursor[i] \
			: game->viewer.color[i]));
		printw("%02x", game->arena[i]);
		attroff(COLOR_PAIR(game->viewer.cursor[i] ? game->viewer.cursor[i] \
			: game->viewer.color[i]));
		game->viewer.cursor[i] ? game->viewer.cursor[i] = 0 : 0;
		if (game->viewer.bold[i] > 0)
		{
			attroff(A_BOLD);
			game->viewer.bold[i] -= 1;
		}
		printw(" ");
		if ((i + 1) % 64 == 0)
			printw("\n");
	}
	print_stats(game);
}
