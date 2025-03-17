/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:01:50 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/17 23:30:11 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void ft_map_error(char *error_msg)
{
    printf("%s", error_msg);
    // Print a stack trace or add debug info
    printf("Error location: %s\n", __func__);
    exit(EXIT_FAILURE);
}

int ft_isspace(char s)
{
    if (s == ' ' || s == '\t' || s == '\n' || s == '\v' || s == '\f' || s == '\r')
        return (1);
    return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;

	if (str != NULL)
		save = str;
	if (!save)
		return (NULL);
	while (*save && ft_strchr(delim, *save))
		save++;
	if (*save == '\0')
		return (NULL);
	token = save;
	while (*save && !ft_strchr(delim, *save))
		save++;
	if (*save)
	{
		*save = '\0';
		save++;
	}
	return (token);
}

/*
** ft_strcspn : renvoie la longueur initiale de la portion de s
** qui ne contient aucun caractère présent dans reject.
*/
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
