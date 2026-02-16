/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   haris.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:49:21 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/16 15:49:22 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARIS_H
# define HARIS_H

# include "lists.h"
# include "expand.h"

void	free_data(t_expand *data);
void	free_arr(char **arr);
void	free_all(t_total_info **total);

#endif
