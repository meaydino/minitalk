/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:51:57 by meaydino          #+#    #+#             */
/*   Updated: 2024/10/21 13:23:03 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	rng;

	if (!s)
		return (NULL);
	rng = ft_strlen(s);
	if (start >= rng)
		return (ft_strdup(""));
	if (len > rng - start)
		len = rng - start;
	string = (char *)malloc(len + 1);
	if (!string)
		return (NULL);
	ft_strlcpy(string, s + start, len + 1);
	return (string);
}
