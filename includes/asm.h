/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbragard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:09:36 by qbragard          #+#    #+#             */
/*   Updated: 2019/09/12 15:01:12 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdarg.h>
# include "op.h"
# include "../libft/includes/libft.h"

typedef struct		s_ins
{
	int				op_code;
	long long		*arg_1;
	long long		*arg_2;
	long long		*arg_3;
	int				pos;
	int				instruc_size;
	struct s_ins	*next;
}					t_ins;

typedef struct		s_info
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				*file;
	char				*tmp;
	int					line;
	int					column;
	int					current_pos;
	int					error;
	int					fd;
	struct s_ins		*ins;
	struct s_label_list	*labels;
}					t_info;

typedef struct		s_label_list
{
	char				*name;
	int					number;
	int					pos;
	struct s_label_list	*next;
}					t_label_list;

t_ins				*ins_malloc_initialization(t_info *info);
long				ind_recon(t_info *info);
long				direct_recon(t_info *info);
int					check_name(t_info *info);
int					check_comment(t_info *info);
int					get_instruction_list(t_info *info, t_ins *ins);
int					print_argument_type_code(t_info *info, t_ins *ins);
int					ft_usage(int error, t_info *info);
int					check_file(int ac, char **av, t_info *info);
int					instructions_init(t_info *info, t_ins *ins);
int					operation_recon(t_info *info);
int					args_counter(t_info *info, t_ins *ins);
int					args_recon(t_info *info, t_ins *ins);
int					check_label_exist(t_info *info, char *label_to_check);
int					add_pos_to_label_num(t_info *info, int num);
int					ft_zjmp(t_info *info, t_ins *ins);
int					ft_ldi(t_info *info, t_ins *ins);
int					ft_sti(t_info *info, t_ins *ins);
int					ft_fork(t_info *info, t_ins *ins);
int					ft_lld(t_info *info, t_ins *ins);
int					ft_lldi(t_info *info, t_ins *ins);
int					ft_lfork(t_info *info, t_ins *ins);
int					ft_aff(t_info *info, t_ins *ins);
int					ft_live(t_info *info, t_ins *ins);
int					ft_ld(t_info *info, t_ins *ins);
int					ft_st(t_info *info, t_ins *ins);
int					ft_add(t_info *info, t_ins *ins);
int					ft_sub(t_info *info, t_ins *ins);
int					ft_and(t_info *info, t_ins *ins);
int					ft_or(t_info *info, t_ins *ins);
int					ft_xor(t_info *info, t_ins *ins);
int					reg_recon(t_info *info);
int					ind_lab_recon(t_info *info);
int					label_recon(t_info *info);
int					which_arg(t_info *info);
int					next_arg(t_info *info);
int					next_op(t_info *info);
int					is_authorized(char to_check, int n, ...);
int					is_banned(char to_check, int n, ...);
int					skip_blanks(t_info *info);
int					ignore_comments(t_info *info);
int					add_label(t_info *info, t_ins *ins);
int					discover_new_label(t_info *info);
int					add_instruction(t_info *info, t_ins *ins);
int					which_arg(t_info *info);
int					get_arg(t_info *info, int arg);
int					possible_args(t_info *info, int n, ...);
int					update_labels(t_info *info);
int					print_magic_header(t_info *info);
int					print_n_bytes(t_info *info, int value, int n);
int					print_instructions(t_info *info);
int					print_arguments(t_info *info, t_ins *ins);
int					reg_writing(t_info *info, long long *arg_n);
int					dir_writing(t_info *info, long long *arg_n, t_ins *ins);
int					ind_writing(t_info *info, long long *arg_n);
int					lab_writing(t_info *info, long long *arg_n, t_ins *ins);
int					free_for_all(t_info *info);
int					ft_free_string(char **s);
void				update_sizes(t_info *info, t_ins *ins);

#endif
