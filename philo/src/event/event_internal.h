/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:19:29 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 14:20:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_INTERNAL_H
# define EVENT_INTERNAL_H

# include "event.h"

void	push_event(t_event_queue *queue, t_event *event);
t_event	*pop_event(t_event_queue *queue);

#endif