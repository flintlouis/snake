/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   snake.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 12:03:10 by nvreeke        #+#    #+#                */
/*   Updated: 2019/05/26 17:13:33 by FlintLouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_H
# define SNAKE_H

# include "mlx.h"
# include "libft.h"

#include <stdio.h>		///

# define GRID			10
# define HEIGHT			400
# define WIDTH			600
# define MEM(x)			(x*)ft_memalloc(sizeof(x))
# define KEYCONF		mlx->keyconf
# define SNAKEHEAD		mlx->snake_head
# define APPLE			mlx->apple
# define GAME			mlx->game

# define KEY_ESC		53
# define KEY_SPACE		49
# define KEY_LSHIFT		257
# define KEY_RSHIFT		258
# define KEY_UP			126
# define KEY_DOWN		125
# define KEY_RIGHT		124
# define KEY_LEFT		123
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_PLUS		24
# define KEY_MIN		27
# define KEY_R			15
# define KEY_G			5
# define KEY_B			11
# define L_MOUSE		1
# define R_MOUSE		2
# define WHEEL_FORW		4
# define WHEEL_BACK		5
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_P			35

typedef unsigned char	t_byte;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_apple
{
	int					on;
	t_point				pos;
}						t_apple;

typedef struct			s_snake
{
	t_point				cur_pos;
	t_point				old_pos;
	struct s_snake		*next;	
}						t_snake;

typedef struct			s_colour
{
	t_byte				r;
	t_byte				g;
	t_byte				b;
}						t_colour;

typedef	struct			s_keyconf
{
	int					move;
	long				speed;
	long				ms;
	int					score;
	int					nitro;
	char				updated:1; /* ONLY USES ONE BIT */
}						t_keyconf;

typedef	struct			s_game
{
	int					ai;
	int					players;
	int					map;
	int					game_over;
	int					menu;
	int					p1;
	int					p2;
	long				start_text;
	t_colour			menu_colour;

}						t_game;

typedef	struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*image;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_game				*game;
	t_apple				*apple;
	t_keyconf			**keyconf;
	t_snake				**snake_head;
}						t_mlx;

int 					check_collision(t_snake *snake_head, t_snake *body);
void					move_snake_body(t_snake *body, t_point new_pos);
void					move_snake_head(t_snake *snake, int move);
void					no_sides(t_snake *snake);
void					delete_snake(t_snake *snake);

int						mouse_move(int x, int y, t_mlx *mlx);
int						mouse_press(int button, int x, int y, t_mlx *mlx);
int						mouse_release(int button, int x, int y, t_mlx *mlx);
int						close_window(void *ptr);
int						release_key(int key, t_mlx *mlx);
int						press_key(int key, t_mlx *mlx);
int						start_snake(t_mlx *mlx);
void					turn_left(int *move);
void					turn_right(int *move);
void					ai_snake(t_mlx *mlx);
void					draw_snake(t_mlx *mlx, int player);
void					move_snake(t_mlx *mlx, int player);
void					place_apple(t_mlx *mlx);
void					check_apple(t_mlx *mlx, int player);
void					background(t_mlx *mlx);
void					init_keyconf(t_mlx *mlx);
void					add_snake_body(t_snake *snake_head);
void					put_pixel(int x, int y, t_mlx *mlx, t_colour colour);
void					setup_snake(void);
void					put_square(t_mlx *mlx, t_point pixel, t_colour colour);
void					init_snake(t_mlx *mlx);
void					ft_wait(int sec, long nsec);
void					menu(t_mlx *mlx);
void					menu_title(t_mlx *mlx);
void					setup_game(t_mlx *mlx);
long					time_between_frames(void);
t_point					random_pixel(void);

#endif
