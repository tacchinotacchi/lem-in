/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:20:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 22:26:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

int     store_ants(t_lemin *info, char *line, int index)
{
    info->ants = ft_atoi(line);
    return (index);
}

int     store_commands(t_lemin *info, char *line, int index)
{
	(void)info;
	(void)line;
	/*TODO lol*/
    return (index);
}

int     store_comments(t_lemin *info, char *line, int index)
{
    list_add(&(info->comments), list_new(line, ft_strlen(line)));
    return (index);
}
