/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_resolution_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanty <alanty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:26 by alanty            #+#    #+#             */
/*   Updated: 2025/01/09 18:33:43 by alanty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_atoi2(const char *str, t_recup *recup)
{
	int	sum;

	sum = 0;
	if (str[1] != ' ' || ft_charinstr((char *)str, ',') == 1)
		recup->erreur = 2;
	while (str[recup->i] == ' ' || str[recup->i] == '\t' || str[recup->i] == ','
		|| str[recup->i] == '\n' || str[recup->i] == '\r'
		|| str[recup->i] == '\v' || str[recup->i] == '\f')
		recup->i++;
	if (str[recup->i] == '-' || str[recup->i] == '+')
		recup->erreur = 2;
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
	{
		if (sum > 21474636)
			break ;
		sum = (sum * 10) + (str[recup->i] - 48);
		recup->i++;
	}
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
		recup->i++;
	return (sum);
}

int	ft_atoi3(const char *str, t_recup *recup)
{
	int	verify;

	verify = 0;
	if (str[1] != ' ')
		recup->erreur = 2;
	ft_atoi3_check(str, recup);
	while (str[recup->i] == ' ' || str[recup->i] == '\t' || str[recup->i] == ','
		|| str[recup->i] == '\n' || str[recup->i] == '\r'
		|| str[recup->i] == '\v' || str[recup->i] == '\f')
	{
		recup->i++;
		verify = 0;
		if (str[recup->i] >= '0' && str[recup->i] <= '9')
			recup->indicateur2++;
		while (str[recup->i] >= '0' && str[recup->i] <= '9')
		{
			verify = (verify * 10) + str[recup->i] - 48;
			recup->sum = (recup->sum * 10) + (str[recup->i] - 48);
			recup->i++;
		}
		if (verify > 255 || verify < 0)
			recup->erreur = 2;
	}
	return (recup->sum);
}

int	ft_path_texture_helper(char *str, char **texture, t_recup *recup, int j);

int	ft_path_texture(char *str, char **texture, t_recup *recup, int j)
{
	recup->count2 = 0;
	if (*texture != NULL)
	{
		recup->erreur = 2;
		return (0);
	}
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
		|| ft_strlen2(str) <= 2)
		recup->erreur = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			recup->erreur = 2;
		j++;
	}
	return (ft_path_texture_helper(str, texture, recup, j));
}

int	ft_path_texture_helper(char *str, char **texture, t_recup *recup, int j)
{
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)));
	if (!(*texture))
		recup->erreur = 2;
	while (str[j] != '\0')
	{
		(*texture)[recup->count2] = str[j];
		recup->count2++;
		j++;
	}
	(*texture)[recup->count2] = '\0';
	return (0);
}

void	ft_texture(char *str, t_recup *recup)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path_texture(str, &recup->no, recup, 2);
	else if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path_texture(str, &recup->so, recup, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path_texture(str, &recup->we, recup, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path_texture(str, &recup->ea, recup, 2);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ft_path_texture(str, &recup->sp, recup, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
		&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C' && str[0] > 65
		&& str[0] < 122)
		recup->erreur = 2;
	j++;
}
