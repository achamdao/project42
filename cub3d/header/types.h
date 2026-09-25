/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:44:25 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:23:53 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_stack		t_stack;
typedef struct s_env		t_env;
typedef struct s_here_doc	t_here_doc;
typedef struct s_info		t_info;
typedef struct s_info_cmd	t_info_cmd;
typedef struct s_files		t_files;

extern int					g_lobal_var;

enum e_builtin
{
	FIAL = -1,
	BNONE,
	ECHO,
	CD,
	EXPORT,
	EXIT,
	PWD,
	UNSET,
	ENV
};

enum e_token
{
	NONE = 0,
	SUCCESS = -20,
	PIPE = '|',
	INP_RED = 270,
	OUT_RED = 271,
	APPEND = 256,
	HERE_DOC = 257,
	VAR = '$',
	EMPTY_STR = 258,
	WORD = 259,
	EQUAL = '=',
	SINGLE_QT = '\'',
	DOUBLE_QT = '\"',
	OPEN_S_Q = 260,
	CLOSE_S_Q = 261,
	OPEN_D_Q = 262,
	CLOSE_D_Q = 263,
	CMD = 264,
	IN_FILE = 265,
	APP_FILE = 266,
	HER_FILE = 267,
	D_PIPE = 268,
	OUT_FILE = 269,
	NEW_LINE = '\n',
	GARBAGE_VALUE = 272,
	AMBIGUOUS_REDIRECT = 273,
	EXPANSION = 274,
	AKATSUKI = 275,
	AMBIGUOUS = 276,
	NOT_VALID = -3,
	FAILER = -1,
	ERROR = -2
};

enum e_metachar
{
	META_AMPERSAND = '&',
	META_SEMICOLON = ';',
	META_LPAREN = '(',
	META_RPAREN = ')',
	META_LBRACE = '{',
	META_RBRACE = '}',
	META_LBRACKET = '[',
	META_RBRACKET = ']',
	META_BACKSLASH = '\\',
	META_BACKTICK = '`',
	META_TILDE = '~',
	META_EXCLAMATION = '!',
	META_HASH = '#',
	META_PERCENT = '%',
	META_CARET = '^',
	META_STAR = '*',
	META_QUESTION = '?',
	META_COLON = ':'
};

typedef struct s_stack
{
	char			*word;
	short			token;
	int				is_space;
	int				prev_is_space;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_here_doc
{
	char				*limeter;
	char				last_limiter;
	char				quote_exists;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_files
{
	char			*file;
	short			token;
	struct s_files	*next;
	struct s_files	*prev;
}	t_files;

typedef struct s_info
{
	t_files		*file;
	t_here_doc	*here_doc;
	t_stack		*info;
	int			*is_here_doc;
	int			number_cmd;
	short		error;
	short		temp_error;
}	t_info;

typedef struct s_info_cmd
{
	char			**cmd;
	char			*path;
	enum e_builtin	buiilding;
	int				tmp;
	t_files			*my_files;
	int				fd_here_doc;
}	t_info_cmd;

typedef struct s_env
{
	char			*name_var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*user_stack;
	t_stack	*stack;
	t_files	*files;
	char	**envp;
}	t_data;

typedef struct s_pipeline_data
{
	t_info_cmd	*cmds;
	t_data		*data;
	int			total_cmds;
	int			**pipes;
}	t_pipeline_data;

#endif
