/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:01:39 by mnachit           #+#    #+#             */
/*   Updated: 2024/05/03 15:04:22 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *substr;
    size_t i;

    if (!s)
        return NULL;
    if (start >= ft_strlen(s))
        return ft_strdup("");
    if (start + len > ft_strlen(s))
        len = ft_strlen(s) - start;
    substr = (char *)malloc(sizeof(char) * (len + 1));
    if (!substr)
        return NULL;
    i = 0;
    while (i < len && s[start + i])
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return substr;
}