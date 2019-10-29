/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <lzimmerm@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:33:27 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 15:22:57 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>

/*
** Index modulos.
*/

# define MODM(x) (x) % MEM_SIZE < 0 ? (x) % MEM_SIZE + MEM_SIZE : (x) % MEM_SIZE
# define MODI(x) (x) % IDX_MOD
# define TOT_SIZ (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
# define BLACK   "\033[90;1m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[36m"
# define EOC     "\033[0m"

/*
** Processus.
*/

typedef struct	s_proc
{
	struct s_proc	*next;
	unsigned char	id;
	char			carry;
	char			alive;
	char			op_code;
	int				reg[REG_NUMBER];
	int				cycles_to_wait;
	int				jump;
	int				pc;
}				t_proc;

/*
** Players.
*/

typedef struct	s_player
{
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	prog[CHAMP_MAX_SIZE + 1];
	char			alive;
	char			nbr;
	int				lives;
	int				prog_len;
	int				nb_proc;
}				t_player;

/*
** Arena.
*/

typedef struct	s_viewer
{
	unsigned char	color[MEM_SIZE];
	unsigned char	cursor[MEM_SIZE];
	unsigned char	bold[MEM_SIZE];
	int				button;
	int				sleep;
}				t_viewer;

/*
** Game data.
*/

typedef struct	s_game
{
	struct s_proc	*proc;
	unsigned char	arena[MEM_SIZE];
	t_player		player[MAX_PLAYERS];
	t_viewer		viewer;
	t_op			op_tab[17];
	int				nb_lives;
	int				nb_check;
	int				cycle_to_die;
	int				tot_cycle;
	int				cycle;
	int				nb_players;
	int				dump;
	char			next_p_num;
	char			last_alive;
	char			error;
	char			running;
	char			viewer_mod;
	void			(*exec_op[17])(t_proc *, struct s_game *);
}				t_game;

/*
** Corewar functions.
*/

int				get_param(t_game *game, t_proc *proc, char type, char mod);
int				coding_byte(unsigned char byte, char par[3], char mod, int *j);
int				get_short(unsigned char *arena, int index);
int				get_int(unsigned char *arena, int index);
char			parser(char **argv, t_game *game);
char			add_player(t_game *game, unsigned char *file, int nbr, int pl);
char			init_game(t_game *game);
void			corewar(t_game *game);
void			init_curses(void);
void			print_viewer(t_game *game);
void			viewer_buttons(t_game *game);
void			print_result(t_game *game);
void			print_map(t_game *game);
void			free_proc(t_game *game);
void			kill_proc(t_game *game);
void			set_op_tab(t_game *game);
void			get_functions(t_game *game);
void			op_live(t_proc *proc, t_game *game);
void			op_ld(t_proc *proc, t_game *game);
void			op_st(t_proc *proc, t_game *game);
void			op_add(t_proc *proc, t_game *game);
void			op_sub(t_proc *proc, t_game *game);
void			op_and(t_proc *proc, t_game *game);
void			op_or(t_proc *proc, t_game *game);
void			op_xor(t_proc *proc, t_game *game);
void			op_zjmp(t_proc *proc, t_game *game);
void			op_ldi(t_proc *proc, t_game *game);
void			op_sti(t_proc *proc, t_game *game);
void			op_fork(t_proc *proc, t_game *game);
void			op_lld(t_proc *proc, t_game *game);
void			op_lldi(t_proc *proc, t_game *game);
void			op_lfork(t_proc *proc, t_game *game);
void			op_aff(t_proc *proc, t_game *game);
void			dup_proc(t_proc *proc, t_game *game, int idx);
void			write_arena(unsigned char *arena, int index, int val);

#endif
