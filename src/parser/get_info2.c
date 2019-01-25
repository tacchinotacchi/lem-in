/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:20:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 23:15:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

ssize_t     store_ants(t_lemin *info, char *line, ssize_t index)
{
    info->ants = ft_atoi(line);
    return (index);
}

ssize_t     store_commands(t_lemin *info, char *line, ssize_t index)
{
    return (index);
}

ssize_t     store_comments(t_lemin *info, char *line, ssize_t index)
{
    list_add(&(info->comments), list_new(ft_strdup(line), ft_strlen(line + 1)));
    return (index);
}