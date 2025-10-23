/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:28:50 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/23 15:37:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_INTERNAL_H
# define PHILOS_INTERNAL_H

# include "event.h"

void	sleep_untill_time_ms(t_event_queue *event_queue, long int target_time);

#endif