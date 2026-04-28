/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:02:45 by gortiz-j          #+#    #+#             */
/*   Updated: 2025/09/02 14:06:51 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map;
typedef struct s_square
{
	int	size;
	int	x;
	int	y;
}	t_square;

int		validate_map(t_map *map);
void	solve_map(t_map *map, t_square *sq);
int		read_map(char *filename, t_map *map);
void	print_map(t_map *map, t_square sq);
void	free_map(t_map *map);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	*ft_strdup(char *src);
int		read_file_to_buffer(char *filename, char *buf);
char	**split_lines_custom(char *buf, int *line_count);
int		parse_header(char *line, t_map *map);
int		fill_grid(char **lines, t_map *map);

#endif
