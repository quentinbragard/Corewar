/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzimmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:03:11 by lzimmerm          #+#    #+#             */
/*   Updated: 2019/09/10 15:03:45 by lzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
** Initialize players.
*/

static void	init_players(t_game *game)
{
	int	i;

	game->error = 0;
	game->viewer_mod = 0;
	game->next_p_num = 0;
	game->nb_players = 0;
	game->dump = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		ft_memset(game->player[i].name, 0, PROG_NAME_LENGTH + 1);
		ft_memset(game->player[i].comment, 0, COMMENT_LENGTH + 1);
		game->player[i].lives = 0;
		game->player[i].nbr = 0;
	}
}

/*
** Check and validate option arguments.
*/

static char	parse_option(t_game *game, char **argv, int *i)
{
	if (ft_strequ(&argv[*i][1], "dump") && !game->dump \
		&& argv[*i + 1] && ft_check_intmax(argv[*i + 1]))
	{
		game->dump = ft_atoi(argv[*i + 1]);
		(*i) += 2;
		return (0);
	}
	else if (argv[*i][1] == 'n' && !argv[*i][2] && argv[*i + 1] \
		&& (game->next_p_num = ft_atoi(argv[*i + 1])) > 0 \
		&& game->next_p_num <= MAX_PLAYERS && argv[*i + 2])
	{
		(*i) += 2;
		return (0);
	}
	else if (ft_strequ(&argv[*i][1], "viewer"))
	{
		game->viewer_mod = 1;
		(*i) += 1;
		return (0);
	}
	return (1);
}

/*
** Read and parse program arguments. Create players.
*/

char		parser(char **argv, t_game *game)
{
	unsigned char	buff[TOT_SIZ + 1];
	int				fd;
	int				r;
	int				i;
	int				j;

	init_players(game);
	i = 0;
	while (argv[++i] && (j = -1))
	{
		while (argv[i] && argv[i][0] == '-')
			if (parse_option(game, argv, &i) || !argv[i])
				return (!argv[i] ? 0 : (game->error = 1));
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return ((game->error = 2));
		if ((r = read(fd, buff, TOT_SIZ + 1)) <= 0)
			return ((game->error = 3));
		close(fd);
		if (!ft_strstr(argv[i], ".cor") || r > TOT_SIZ \
			|| ++game->nb_players > MAX_PLAYERS \
			|| add_player(game, buff, game->nb_players, r \
				- (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)))
			return ((game->error = 4));
	}
	return (0);
}
