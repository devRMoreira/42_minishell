/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:10:55 by rimagalh          #+#    #+#             */
/*   Updated: 2025/06/09 14:11:27 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//behold an amalgamation of strings
char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total;
	char	*res;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	total = len1 + len2 + len3 + 1;
	res = malloc(sizeof(char) * total);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str1, total);
	ft_strlcat(res, str2, total);
	ft_strlcat(res, str3, total);
	return (res);
}
