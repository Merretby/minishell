/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:13:17 by moer-ret          #+#    #+#             */
/*   Updated: 2024/06/25 10:16:39 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <time.h>
# include <string.h>
# include <unistd.h>

# define PATH_MAX 4096

extern int g_exit_code;

typedef	enum e_type
{
	TOKEN_ID,          // a-zA-Z0-9
	TOKEN_STRING,       //"" ''
	TOKEN_PIPE,         // |
	TOKEN_REDIR_IN,     // <
	TOKEN_REDIR_OUT,    // >
	// TOKEN_DOLLAR,       // $
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HEREDOC,      // <<
	TOKEN_ERROR,
	TOKEN_OUTFILE,
	TOKEN_FILE,
	TOKEN_EOF,
} t_type;

typedef struct handle_signal
{
	int				signal;
}	t_handle_signal;

typedef enum e_rd
{
	CMD = 0,
	REDIR = 1,
	PIPE = 2,
} t_rd;

typedef struct s_args
{
	char			*args;
	struct s_args	*next;
}	t_args;

typedef struct s_token
{
	t_type           type;
	t_args			*args;
	char			**arg;
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
	int				ex_flag;
	int				type;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipe
{
	char 			*value;
	int				type;
	struct s_pipe	*next;
}					t_pipe;

typedef union u_data
{
	t_pipe			*pipe;
	t_cmd			*cmd;
	t_redir			*red;
}					t_data;

typedef struct s_env
{
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
void				lexer_to_next_token(t_lexer **lexer, t_token **token);
t_token				*advance_token(t_lexer *lexer, t_token *token);

// linkedlist
t_token				*ft_lstlast1(t_token *lst);
void				ft_lstadd_back1(t_token **lst, t_token *new);
t_env   			*ft_lstnew2(char *value);
void				ft_lstadd_back2(t_env **lst, t_env *new);


//execution
void ft_execution(t_node *tree, char **env1, int fork_flag);
int	 ft_execute(t_node *tree,  char **env, int fork_flag);

// builtins
int					ft_cd(t_node *node, char **env);
int					ft_echo(t_node *tree);
int					ft_env(char **env);
int					ft_exit(t_node *tree);
char 				**ft_export(t_node *tree, char **env1);
int					ft_pwd(t_node *tree);
char				**ft_unset(t_node *node, char **env1);
int 				ft_strcmp(const char *s1, const char *s2);
// int					ft_builtins(char *str, t_node *tree);
//env
void				take_env(char **env);

// init
t_lexer				*init_lexer(char *content);
t_token				*init_token(int type, char *value, char c);

// parsing
void				helper(t_token **token, char **env);
void				ft_free(t_token **token, t_lexer **lexer);
int					parss_command(t_token *token);

//heredoc
char				*concatenation(t_token *token, int *flaag);
void				heredoc(t_token *token, char **env);
char	*real_expand(char *line, char **env);

//expand
void				expand(t_token **token, char **env);

//free
void delete_node(t_token **head, t_token *node);
void	free_2d(char **str);

#endif 