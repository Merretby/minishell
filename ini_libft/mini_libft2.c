/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:04:58 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/02 18:08:10 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len2(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa2(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = n;
	len = ft_len2(nb);
	str = malloc(len + 1);
	ft_lstadd_back_free(&g_v->adress, init_free(str));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nb != 0)
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (str);
}

int	*retur_nvalue(void)
{
	static int	retur_n = -1;

	return (&retur_n);
}

void	list_to_array(t_token *token)
{
	t_args	*tmp;
	t_args	*tmp2;
	int		i;

	i = 0;
	tmp2 = token->args;
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	token->arg = ft_calloc1(i + 1, sizeof(char *));
	ft_lstadd_back_free(&g_v->adress, init_free(token->arg));
	i = 0;
	tmp = token->args;
	while (tmp)
	{
		token->arg[i] = tmp->args;
		tmp = tmp->next;
		i++;
	}
	token->arg[i] = NULL;
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
