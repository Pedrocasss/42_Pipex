/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:22:47 by psoares-          #+#    #+#             */
/*   Updated: 2023/09/20 20:22:58 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	if (!s1 || !s2)
		return (0);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	ptr[j] = 0;
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int		j;
	char	*ptr;

	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		ptr = (char *)malloc(sizeof(char));
		*ptr = 0;
		return (ptr);
	}
	if (len >= ft_strlen(s))
		len = (ft_strlen(s) - start);
	ptr = (char *)malloc(1 + len);
	if (!ptr)
		return (NULL);
	while (start < ft_strlen(s) && j < len)
	{
		ptr[j] = s[start];
		j++;
		start++;
	}
	ptr[j] = 0;
	return (ptr);
}
