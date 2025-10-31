/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:13:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 16:17:59 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long int	get_time_in_milliseconds(void)
{
	struct timeval	tv;
	long int		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milliseconds);
}

void	sleep_untill_time(long int target_time)
{
	long int	current_time;

	while (1)
	{
		current_time = get_time_in_milliseconds();
		if (current_time >= target_time)
			break ;
		usleep(1000);
	}
}
