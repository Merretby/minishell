/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/03 17:34:25 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lixer
{
	char	c;
	size_t	i;
	char	*content;
} t_lexer;

typedef struct s_token
{
	enum
	{
		TOKEN_ID,           // a-zA-Z0-9
		TOKEN_STRING,       //""
		TOKEN_PIPE,         // | 
		TOKEN_REDIR_IN,     // <
		TOKEN_REDIR_OUT,    // >
		TOKEN_DOLLAR,       // $
		TOKEN_AMPERSAND,    // &
		TOKEN_REDIR_APPEND, // >>
		TOKEN_HEREDOC,      // <<
	} type;
	char *value;
	struct s_token *next;
} t_token;

//lexter
t_lexer *init_lexer(char *content);
void	advance(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);

//token
t_token	*init_token(int type, char *value);
t_token	*lexer_to_next_token(t_lexer *lexer);
t_token	*advance_token(t_lexer *lexer, t_token *token);
t_token	take_string(t_lexer *lexer);
char	*get_the_string(t_lexer *lexer);

//linkedlist
t_token	*ft_lstlast1(t_token *lst);
void	ft_lstadd_back1(t_token **lst, t_token *new);
#endif