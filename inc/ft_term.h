#ifndef FT_TERM_H
#define FT_TERM_H

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <strings.h>
#include <unistd.h>
#include <sys/uio.h>
#include <termios.h>
#include <signal.h>
#include "libft.h"
#include "ft_printf.h"

#define LSEEK(x) ((x >=70 && x <= 72) || (x >= 'C' && x <= 'D'))
#define DEL(x) (x == 51)
#define SCRL(x) (x >= 53 && x <= 54)
#define HIST(x) (x >= 'A' && x <= 'B')
#define SHIFT(x)
#define BUFF_SIZE 1024

int					g_ft_errnum;
extern char			PC;
extern char			*UP;
extern char			*BC;
extern short		ospeed;

typedef struct	s_errstr
{
	int			err;
	char		*str;
	size_t		len;
}				t_errstr;

enum {
	SYSERR,
	TERMGET,
	TGETN,
	TGETZ,
	TGETSTR
};

typedef	struct		s_terminf
{
/* For ioctl purposes */
	struct termios	og; /* no free */
	struct termios	*antishell; /* no free */
/* For terminal initialization */
	char			*term_name; /* no free */
	char			*term_buff; /* FREE */
	char			*line_buffer;
	// t_hashtable		*hashtable;
}					t_terminf;

//
// typedef struct		s_env
// {
// 	t_terminf		*terminfo;
// 	t_hashtable		*hashtable;
// 	char			**envron
// }					t_env;


/* Allocate at sizes of 128 bytes, sequentially, to be arranged in a queue */

typedef struct		s_linebuf
{
	char			*line;
	char			*curr_pos;
	size_t			len;
}					t_linebuf;

/*
**		Error handling (error.c)
*/

void				ft_terror(void);

/*
**		Execution and tty handlers (exec_handlers.c)
*/

int		shsignal_handlers(void);
int		ft_setty(t_terminf *anti);
int		ft_resetty(t_terminf *anti);
int		ft_restoretty(t_terminf *anti);

/*
**		ANSI sequences for cursor movement (cursor_moves.c)
*/

int		ft_curight(t_terminf *anti);
int		ft_curleft(t_terminf *anti);
int		ft_clearscreen(t_terminf *anti);
void	ft_clearline(int clr);
int		ft_curhome(t_terminf *anti);
int		my_stupidput(int chrr);
int		ft_backspace(t_terminf *anti);
int		ft_passinput(t_terminf *anti);

/*
**		dispatcher for interpreting escape sequence (multibyte_dispatch.c)
*/

int		read_multibyte(char byte, int *mpass, t_terminf *anti);
int		line_seek(t_terminf *anti, char byte);


/*
**		read_loop
*/

int		read_loop(t_terminf *shell_env);


/*
**		prompt_utils
*/
void		new_prompt(t_terminf *shell_env);

/*
**		prompt_utils
*/
int			carriage_return(t_terminf *shell_env, char byte, int slash_token)

/*
**		buffer_utils
*/
int			init_buffer(t_terminf *shell_env);
int			handle_buffer(t_terminf *shell_env);

/*
**		keys_handler
*/
int				handle_keys(t_terminf *shell_env, char byte);

#endif
