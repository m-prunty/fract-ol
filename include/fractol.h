/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:38:26 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/29 15:12:24 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# define HEIGHT 1060
# define WIDTH 1060
# define SWIDTH 200 
# define CHUNKS 40
# define FT_PI_3 1.04719755119659774615

/*
 * COLORS
 */
# define BLACK		0x000000	// RGB(0, 0, 0)
# define WHITE		0xFFFFFF	// RGB(255, 255, 255)
# define RED		0xFF0000	// RGB(255, 0, 0)
# define GREEN		0x00FF00	// RGB(0, 255, 0)
# define BLUE		0x0000FF	// RGB(0, 0, 255)

// Psychedelic colors
# define MAGENTA_BURST	0xFF00FF	// A vibrant magenta
# define LIME_SHOCK		0xCCFF00	// A blinding lime
# define NEON_ORANGE	0xFF6600	// A blazing neon orange
# define PSYCHEDELIC_PURPLE 0x660066	// A deep purple
# define AQUA_DREAM		0x33CCCC	// A bright turquoise
# define HOT_PINK		0xFF66B2	// As the name suggests!
# define ELECTRIC_BLUE	0x0066FF	// A radiant blue
# define LAVA_RED		0xFF3300	// A bright, molten red

// Keymap
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_PLUS 61 
# define KEY_MINUS 45 
# define KEY_LT 44 
# define KEY_GT 46 
# define KEY_R 114 
# define KEY_H 104 
# define KEY_O 111 
# define KEY_M 109 
# define KEY_J 106 
# define KEY_S 115 
# define KEY_C 99
# define KEY_I 105
# define KEY_K 107
# define KEY_SPACE 32 

//Error Messages
# define ERR_NONE "no errors detected: "
# define ERR_MALLOC "malloc failed "
# define ERR_INPUT "incorrect input: "
# define ERR_INPUT_VAL "input must b either 'm', 'j x y', or 'b x y'"
# define ERR_INPUT_XY "must be initialised with x y in the form 'j x y'"
# define ERR_MLX "mlx error; "
# define ERR_MLX_INIT "Could not establish mlx_connection"
# define ERR_MLX_WIN "Could not establish mlx_new_window"
# define ERR_MLX_IMG "Could not establish mlx_new_image"
# define ERR_MLX_OVERLAY "Could not create overlay image"
# define ERR_MLX_DISPLAY "mlx_display error"

typedef struct s_data
{
	void	*img;
	char	*pxl_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		is_visible;
}	t_data;

/**
 * @typedef s_complex
 * @brief for storing complex values, x is real and y imaginary
 *
 */
typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

typedef struct s_event
{
	int				keysym;
	t_complex		data;
	struct s_event	*next;
}	t_event;

/**
 * @typedef s_mouse
 * @brief for storing mouse data
 */
typedef struct s_mouse
{
	t_complex	pos;
	t_complex	trans;
	int			is_pressed;
}	t_mouse;

typedef struct s_tri
{
	t_complex		a;
	t_complex		b;
	t_complex		c;
	t_complex		mid_ab;
	t_complex		mid_bc;
	t_complex		mid_ca;
	int				colour;
	struct s_tri	*sub1;
	struct s_tri	*sub2;
	struct s_tri	*sub3;
}	t_tri;

/**
 * @typedef s_fractal
 * @brief 
 */
typedef struct s_fractal
{
	char		*name;
	void		*mlx_con;
	void		*mlx_win;
	t_data		img;
	t_data		side;
	double		zoom;
	t_complex	shift;
	t_complex	range;
	t_complex	c;
	t_complex	wsize;
	t_complex	imgsize;
	t_complex	sidesize;
	int			*offset;
	int			*colour;
	int			colour_shift;
	int			iters;
	int			esc;
	int			show_help;
	t_mouse		mouse;
	t_complex	centre;
	int			str_y;
	char		**info;
	char		**help;
	t_tri		*tri;
	t_event		*events;
	int			frame_count;
	int			debounce_frames;
}	t_fractal;

t_complex	map_complex_tri(t_complex *pixel, t_fractal *f);
void		clean_tri(t_tri *t);
void		update_centre(t_fractal *f);
void		set_triangles(t_tri *parent, t_tri *child,
				t_tri *t, t_tri *parent_tri);
void		def_z_c(t_fractal *f, t_complex *pixel, t_complex *z, t_complex *c);

int			mouse_handler(int button, int x, int y, t_fractal *f);
// ../src/events_handler.c
int			close_handler(t_fractal *f);
int			char_key_handler(int keysym, t_fractal *f);
int			image_key_handler(int keysym, t_fractal *f);
int			key_handler(int keysym, t_fractal *f);

// ../src/events_mouse.c
t_complex	mouse_translate(t_fractal *f, int x, int y);
int			mouse_press(int button, int x, int y, t_fractal *f);
int			mouse_motion(int x, int y, t_fractal *f);
int			mouse_release(int button, int x, int y, t_fractal *f);
void		mouse_zoom(t_fractal *f, int dir);
int			switch_fractal(int keysym, t_fractal *f);

// ../src/events_q.c
void		add_event(t_fractal *f, int keysym, t_complex data);
int			event_loop(t_fractal *f);
void		process_events(t_fractal *f);
void		clear_events(t_fractal *f);

// ../src/events.c
int			move(t_fractal *f, int axis, double delta);
int			inc_iters(t_fractal *f, double delta);
int			zoom(t_fractal *f, int dir);
int			recentre(t_fractal *f);

// ../src/colour.c
int			linear_interpolation(double t, t_fractal *f);
double		smooth(int i, t_complex z);

// ../src/pixel.c
void		pre_calc(t_fractal *f, t_data *data);
void		my_mlx_pixel_put(t_fractal *f, int x, int y, int color);
t_complex	map_complex(t_complex *pixel, t_fractal *f);
void		place_pixel(t_fractal *f, t_complex *pixel);

// ../src/render.c
void		render_f(t_fractal *f);
void		render_chunk(t_fractal *f, int chunk_x, int chunk_y);
void		render_sidebar(t_fractal *f);
void		info_clr_init(t_fractal *f);

t_complex	normalise(t_complex a, t_complex b, double mag);
t_tri		*tri_def(t_tri *tri, t_complex a, t_complex b, t_complex c);

// ../src/em_tri.c
void		set_exact(t_complex *target, t_complex *src);
void		set_midpoint(t_complex *target, t_complex *a, t_complex *b);
void		triangle(t_fractal *f, t_tri *t);
void		place_pixel_triangle(t_fractal *f, t_complex *pixel);

// ../src/sidebar.c
void		clear_sidebar(t_fractal *f);
int			sidestr_help(t_fractal *f);
int			sidestr_info(t_fractal *f);
char		*str_parsed(t_infostr info);
char		*ft_dtostr(double n, int precision);

// ../src/init.c
void		init_f(t_fractal *f);
void		init_sidebar(t_fractal *f);
void		init_events(t_fractal *f);
int			init_values(t_fractal *f);
int			init_serptri(t_fractal *f);

// ../src/main.c
int			error_func(int i, char *info);
void		clean_fractal(t_fractal *f, int n_error, char *info);
double		ft_atof(const char *nptr);
int			check_args(int ac, char **av, t_fractal *f);
int			main(int ac, char **av);

// ../src/maths_util.c
double		ft_complex_abs(t_complex complex);
double		ft_complex_dot(t_complex *a, t_complex *b);
void		ft_complex_exp(double angle, t_complex *result);
t_complex	ft_complex_conjugate(t_complex a);
t_complex	ft_complex_divide(t_complex numerator, t_complex denominator);

// ../src/maths_util.c
double		scale_linear(double n, t_complex p1, t_complex p2);
double		ft_distsqrd(t_complex a, t_complex b);
t_complex	ft_complex_sqrd(t_complex z);
t_complex	ft_complex_sum(t_complex z1, t_complex z2);
int			is_mandelbulb(double x, double y);

#endif
