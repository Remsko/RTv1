/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-cunh <ada-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:46:43 by ada-cunh          #+#    #+#             */
/*   Updated: 2018/01/26 12:46:43 by ada-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdlib.h>
#include "libft.h"

void	ft_exit(char *msg)
{
	if (msg)
		ft_putendl(msg);
	exit(-1);
}
