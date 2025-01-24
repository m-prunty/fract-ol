/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:27:12 by mprunty           #+#    #+#             */
/*   Updated: 2025/01/22 22:58:53 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/**
 * @brief 
 *
 * @param f 
 */
void	clear_sidebar(t_fractal *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH;
		while (x < WIDTH + SWIDTH)
		{
			my_mlx_pixel_put(&f->side, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_con, f->mlx_win, f->side.img, WIDTH, 0);
}

int	sidestr_help(t_fractal *f)
{
	f->help = (char **)malloc(sizeof(char *) * 11);
	f->help[0] = "Controls:";
	f->help[1] = "ESC - Exit";
	f->help[2] = "Arrow keys - Move view";
	f->help[3] = "Mouse wheel - Zoom in/out";
	f->help[4] = "Left click & drag - Select zoom area";
	f->help[5] = "+/- - Increase/decrease iterations";
	f->help[6] = "r - Reset view";
	f->help[7] = "h - Toggle help";
	f->help[8] = "o - Toggle sidebar";
	f->help[9] = "m, j, s - Mandelbrot, Julia, Serpinksi";
	f->help[10] = "space - Change colour";
	f->help[11] = "";
	return (11);
}

int	sidestr_info(t_fractal *f)
{
	t_infostr	data[12];
	int			i;

	i = 0;
	 
	info_clr_init(f);
	data[0] = (t_infostr){"", (t_complex){0, 0}};
	data[1] = (t_infostr){"Iterations:  ", (t_complex){f->iters, 0}};
	data[2] = (t_infostr){"Zoom:        ", (t_complex){f->zoom, 0}};
	data[3] = (t_infostr){"Shift:       ", f->shift};
	data[4] = (t_infostr){"Mouse:       ", f->mouse.start};
	data[5] = (t_infostr){"C value:     ", f->c};
	data[6] = (t_infostr){"Centre:      ", f->centre};
	data[7] = (t_infostr){"Esc:         ", (t_complex){f->esc, 0}};
	data[8] = (t_infostr){"Colour shift:", (t_complex){f->colour_shift, 0}};
	data[9] = (t_infostr){"", (t_complex){0, 0}};
	if (f->side.is_visible)
	{
		*f->info = ft_strjoin("Fractal:     ", f->name);
		while (data[++i].str)
			*(f->info + i) = str_parsed(data[i]);
	}
	return (i);
}

char	*str_parsed(t_infostr info)
{
	char	*res;
	char	*x;
	char	*y;
	int		len;

	len = ft_strlen(info.str);
	x = ft_dtostr(info.c.x, 2);
	y = ft_dtostr(info.c.y, 2);
	len += ft_strlen(x) + ft_strlen(y) + 2;
	res = (char *)malloc(sizeof(char ) * len);
	ft_strlcpy(res, info.str, ft_strlen(info.str) + 1);
	if (info.c.x != 0)
	{
		ft_strlcat(res, x, len);
		if (info.c.y != 0)
		{
			ft_strlcat(res, " ", len);
			ft_strlcat(res, y, len);
		}
	}
	free(x);
	free(y);
	return (res);
}

char	*ft_dtostr(double n, int precision)
{
	char	*str;
	int		len;
	int		i;
	char	*frac;
	char	*intg;

	i = (int)(n);
	frac = ft_itoa(fabs(n - i) * pow(10, precision));
	intg = ft_itoa((int)(n));
	len = ft_strlen(intg) + precision + 2;
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, intg, len);
	if (ft_strncmp(frac, "0", len))
	{
		ft_strlcat(str, ".", len);
		ft_strlcat(str, frac, len);
	}
	free(frac);
	free(intg);
	return (str);
}
