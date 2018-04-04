/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2018/03/29 16:24:10 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERM_H
# define FT_TERM_H


# include <curses.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_printf.h"

# define BUFF_SIZE 1024
# define UNSET (void *)

int					g_ft_errnum;

enum {
	CURSOR_MOVE,
	DEL_KEY,
	SCROLL,
	HISTORY,
	SHIFT
};

enum {
	C_A,
	C_E,
	C_G,
	C_H,
	C_J,
	C_L,
	C_M,
	C_O,
	C_V,
	C_W
};

enum {
	SYSERR,
	TERMGET,
	TGETN,
	TGETZ,
	TGETSTR
};

typedef struct	s_vertex
{
	int		x;
	int		y;
}				t_vertex;

typedef struct	s_cursor
{
	t_vertex		og_position;
	size_t			position;
	char			*buffer;

}				t_cursor;

typedef struct	s_errstr
{
	int			err;
	char		*str;
	size_t		len;
}				t_errstr;

typedef struct		s_buffer
{
	char			*buff;
	size_t			length;
	size_t			max_size;
}					t_buffer;

typedef struct		s_tokens
{
	int				mpass;
	int				bslash;
	int				control_v;
}					t_tokens;

typedef	struct		s_terminf
{
	struct termios		original_tty; /* no free */
	struct termios		*shell_tty; /* FREE */
	struct winsize		window;
	t_buffer			*buffer;
	t_cursor			cursor;
	t_tokens			tokens;
	// t_hashtable		*hashtable;
	int					prompt_length;
	char				*term_name; /* no free */
	char				*term_buff; /* FREE */
}					t_terminf;


//
// typedef struct		s_env
// {
// 	t_terminf		*terminfo;
// 	t_hashtable		*hashtable;
// 	char			**envron
// }					t_env;

/*
**		Error handling (error.c)
*/

void				ft_terror(void);

/*
**		Execution and tty handlers (exec_handlers.c)
*/

int		shsignal_handlers(void);
int		ft_setty(void);
int		ft_resetty(void);
int		ft_restoretty(void);

/*
**		ANSI sequences for cursor movement (cursor_moves.c)
*/

int		ft_curight(void);
int		ft_curleft(void);
int		ft_clearscreen(void);
void	ft_clearline(int clr);
int		ft_curhome(void);
int		my_putchar(int chrr);
int		ft_passinput(void);

/*
**		dispatcher for interpreting escape sequence (multibyte_dispatch.c)
*/

int		multibyte_dispatch(char byte);
int		control_dispatch(char byte);


/*
**		read_loop
*/

int		read_loop(void);


/*
**		prompt_utils
*/

void		new_prompt(char *prompt);
void		reset_prompt();
void		back_prompt(void);

/*
**		prompt_utils
*/
int			ft_carriage_return(void);

/*
**		buffer_utils
*/
int			init_buffer(void);
int			reset_buffer(void);
int			resize_buffer(void);
int			reprint_buffer(void);


/*
**		keys_handler
*/

int				handle_keys(char byte);

/*
**		history
*/
int			add_buff_to_history(char *buffer);
int			open_history(void);

/*
**		cursor motions=
*/
void		move_cursor(t_cursor *cursor);
void		cursor_to_right(t_cursor *cursor);
void		cursor_to_left(t_cursor *cursor);
void		cursor_to_home(t_cursor *cursor);
void		cursor_to_end(t_cursor *cursor);

/* ft_linemove */

int		ft_linemove(char byte);

/*
**		screen info
*/

int		get_window_size(void);

/*
**		utils
*/

void		get_cursor_first_position(void);

/*
**		utils
*/

void		control_c(int c);
int			control_a(void);
int			control_e(void);
int			control_l(void);
int			control_newline(void);
int			control_g(void);
int			control_h(void);
int			control_j(void);
int			control_m(void);
int			control_o(void);
int			control_v(void);
int			control_w(void);
int			ft_backspace(void);
int			ft_delete(char byte);

t_terminf	g_shell_env;

/*
**		backslash handler
*/
int		backslash_char(void);

/*
**		update screen utils
*/
void		update_end_of_screen(void);
void		update_buffer(char *buffer);


#endif