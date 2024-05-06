/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/06 16:59:23 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_cmd
{
	char			*cmd; 
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_redir
{
	t_pipe			*pipe;
	// char *file;
	// char *type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_lixer
{
	char			c;
	size_t			i;
	char			*content;
}					t_lexer;

typedef	enum e_type
{
	TOKEN_ID,          // a-zA-Z0-9
	TOKEN_STRING,       //"" ''
	TOKEN_PIPE,         // |
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	TOKEN_DOLLAR,       // $
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_OUTFILE,
	TOKEN_FILE,
} t_type;

typedef struct s_token
{
	t_type           type;
	int				helper_flag;
	int 			flag;
	char			*value;
	struct s_token	*next;
}					t_token;

// lexter
void				advance(t_lexer *lexer);
void				skip_whitespace(t_lexer *lexer);
char				*get_the_word(t_lexer *lexer);
char				*get_the_string(t_lexer *lexer, char c);
t_token				*advance_token(t_lexer *lexer, t_token *token);
void				skip_whitespace(t_lexer *lexer);
void				advance(t_lexer *lexer);
char				*defin(int c);

// token
void				lexer_to_next_token(t_lexer *lexer, t_token **token);
t_token				*advance_token(t_lexer *lexer, t_token *token);
// t_token				take_string(t_lexer *lexer);

// linkedlist
t_token				*ft_lstlast1(t_token *lst);
void				ft_lstadd_back1(t_token **lst, t_token *new);

//env
void				take_env(char **env);
// void				print_env(t_env *env);

// init
t_lexer				*init_lexer(char *content);
t_token				*init_token(int type, char *value, char c);
t_pipe				*init_pipe(t_cmd *cmd);
t_cmd				*init_cmd(char *cmd);
t_redir				*init_redir(t_pipe *pipe);
t_tree				*init_tree(char *cmd);

// parsing
void				join_cmd(t_token *token);
void				ft_free(t_token **token, t_lexer **lexer);

#endif