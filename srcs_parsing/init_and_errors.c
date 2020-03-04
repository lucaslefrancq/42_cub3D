/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:49:53 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/27 18:27:45 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Init the structure by putting char * to NULL and for each tab of int by
** putting each value of tabs to -1, so we can check during the parsing if we
** already have treated the parameter or not.
*/
void	struct_init_par(t_pars *par)
{
	par->fd = -1;
	par->reso[0] = -1;
	par->reso[1] = -1;
	par->path_no = NULL;
	par->path_so = NULL;
	par->path_ea = NULL;
	par->path_we = NULL;
	par->path_sp = NULL;
	par->flo_rgb = -1;
	par->sky_rgb = -1;
	par->map = NULL;
}

/*
** Allow to free each elements of the structure, including each line of **map
** and close the file descriptor.
*/
void	struct_free(t_pars *par)
{
	int i;

	i = -1;
	par->fd != -1 ? close(par->fd) : 0; //if there is a flux, we close it
	free(par->path_no);
	free(par->path_so);
	free(par->path_ea);
	free(par->path_we);
	free(par->path_sp);
	if (par->map)
	{
		while (par->map[++i]) // until we reach the NULL *ptr in map
			free(par->map[i]);
		free(par->map);
	}
}

/*
** Print the error msg (= str), and if par exist free each elements of the 
** structure filled with map parameters. Free also one char * (line), send NULL
** into it if there is nothing to free. Then close the file descriptor and exit.
*/
int		error_msg(char *str, t_pars *par, char *line)
{
    printf("Error\n%s", str);
	if (par)
		struct_free(par); //also close file descriptor
	free(line);
	exit(EXIT_FAILURE);
}

/*
** Check if there is only one argument (the map) and if the extension of the
** map file is correct. Call error_msg in case of error.
*/
int     check_arg(int ac, char **av)
{
    int i;

    i = 0;
    if (ac < 2)
        error_msg("Arguments : no file, enter it with the first argument\n", NULL, NULL);
    else if (ac > 2)
        error_msg("Arguments : too many arguments, enter only the map file\n", NULL, NULL);
    else
    {
        while (av[1][i])
            i++;
        i -= 4;
        if (!ft_strcmp(&av[1][i], ".cub"))
            return (1);
        error_msg("Arguments : file map must end by \".cub\"\n", NULL, NULL);
    }
    return (-1);
}