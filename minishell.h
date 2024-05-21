/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/05/21 14:49:03 by moer-ret         ###   ########.fr       */
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

# define PATH_MAX 4096

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

typedef enum e_rd
{
	CMD = 0,
	REDIR = 1,
	PIPE = 2,
} t_rd;


typedef struct s_token
{
	t_type           type;
	int				helper_flag;
	int 			flag;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*value;
	int 			type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*value;
	char			**args;
	int				type;
	struct s_cmd	*next;
}					t_cmd;

typedef union u_data
{
	t_cmd			*cmd;
	t_redir			*red;
}					t_data;

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

typedef struct t_node
{
	t_token			*token;
	t_rd			type;
	t_data			*data;
	t_redir			*red;
	t_env			*env;
	char 			**env1;
	struct t_node	*left;
	struct t_node	*right;
}					t_node;

t_node				*new_node(t_token *token);
t_node				*rederiction(t_token **token);
t_node				*command(t_token **token);
t_node				*pipeline(t_token **token);

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

// linkedlist
t_token				*ft_lstlast1(t_token *lst);
void				ft_lstadd_back1(t_token **lst, t_token *new);


//execution
void    ft_execution(t_node *moad);
void	heredoc(t_token *token);

// builtins
int					ft_cd(t_node *node);
int					ft_echo(t_node *tree);
int					ft_env(t_node *tree);
int					ft_exit(t_node *tree);
int					ft_export(t_node *tree);
int					ft_pwd(t_node *tree);
int					ft_unset(t_node *tree);
// int					ft_builtins(char *str, t_node *tree);

//env
void				take_env(char **env);

// init
t_lexer				*init_lexer(char *content);
t_token				*init_token(int type, char *value, char c);

// parsing
void				helper(t_token *token, char **env);
void				ft_free(t_token **token, t_lexer **lexer);
int					parss_command(t_token *token);

char	*concatenation(t_token *token);

#endif 