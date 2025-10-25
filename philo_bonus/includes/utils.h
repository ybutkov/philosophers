/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:59:35 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/24 14:27:22 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

long int		get_time_in_milliseconds(void);
int				between(long long value, long long left, long long right);
int				in_set(char ch, char *set);
long int		ft_max(long int a, long int b);
unsigned int	hash(char *key);
int				ft_atoi(const char *str);
void			free_and_set_null(void **ptr);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_itoa(int n);
size_t			ft_strlen(const char *s);

#endif