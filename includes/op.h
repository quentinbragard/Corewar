/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzimmerm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:26:01 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/12 14:54:47 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** All sizes are counted in bytes.
** An integer is worth 32 bits.
*/

# define INT_MAX 				2147483647
# define PRIME					5839
# define OP_SIZE				1

# define T_REG_SIZE				1
# define T_DIR_SIZE				4
# define T_IND_SIZE				2
# define T_LAB_SIZE				2

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** Argument types for the operations.
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define T_IND_LAB				16

/*
** Champion binary description.
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** Operations description.
*/

typedef struct		s_op
{
	char		name[PROG_NAME_LENGTH];
	int			nb_params;
	t_arg_type	params_type[3];
	int			op_code;
	int			cycles;
	char		description[50];
	int			coding_byte;
	int			label_size;
}					t_op;

extern t_op			g_op_tab[17];

#endif
