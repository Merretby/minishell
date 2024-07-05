/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:40:59 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/05 12:13:12 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
		s1 = "";
	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = -1;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_lstadd_back_free(&g_v->adress, init_free(ptr));
	if (!ptr)
		return (NULL);
	while (s1 && s1[++i])
		ptr[i] = s1[i];
	while (s2 && s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

void	*ft_calloc1(size_t nmemb, size_t size)
{
	void	*str;
	size_t	i;

	i = -1;
	if (size != 0 && nmemb > (i / size))
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, (size * nmemb));
	return (str);
}

char	*ft_strdup1(const char *src)
{
	size_t		i;
	size_t		size;
	char		*ls;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	ls = malloc((size + 1) * sizeof(char));
	ft_lstadd_back_free(&g_v->adress, init_free(ls));
	if (!ls)
		return (NULL);
	while (src[i] != '\0')
	{
		ls[i] = (char )src[i];
		i++;
	}
	ls[i] = '\0';
	return (ls);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup1(""));
	else if (ft_strlen(s + start) < len)
	{
		str = malloc(ft_strlen(s + start) + 1);
		ft_lstadd_back_free(&g_v->adress, init_free(str));
	}
	else
	{
		str = malloc(len + 1);
		ft_lstadd_back_free(&g_v->adress, init_free(str));
	}
	if (!str)
		return (NULL);
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
