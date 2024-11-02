/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:43:28 by epresa-c          #+#    #+#             */
/*   Updated: 2021/11/10 14:57:54 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		k;
	size_t		needle_len;
	char		*ptr;

	i = 0;
	ptr = (char *)haystack;
	needle_len = ft_strlen(needle);
	if (needle_len == 0 || haystack == needle)
		return (ptr);
	while (ptr[i] && i < len)
	{
		k = 0;
		while (ptr[i + k] != '\0' && needle[k] != '\0'
			&& ptr[i + k] == needle[k] && i + k < len)
			k++;
		if (k == needle_len)
			return (ptr + i);
		i++;
	}
	return (0);
}
