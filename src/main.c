#include <mlx.h>
#include <libft.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
static unsigned long int next = 1;

int ft_rand(void)  /* RAND_MAX assumed to be 32767. */
{
    next = next * 1103515245 + 12345;
    return (unsigned)(next/65536) % RAND_MAX;// 32768;
}

void ft_srand(unsigned seed)
{
    next = seed;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel/ 4 ));
	*(unsigned int*)dst = color ;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

draw_circle( int h, int k, int r, t_data *img)
{
	float dy = 0;
	float dx = 0;
	int  col =0;
	float maxh;
	float maxw;
	int pi = M_PI;
	int theta = 0 ;

	//col = 0x00FF0000;

	maxh = r+h;
	maxw = r+k;
	while ((theta)++ <  2*pi*pow(r,2)){
		dx = r * cos( theta ) +h + (ft_rand()% 4);
		dy = r * sin( theta ) +k + (ft_rand()% 4);
		//printf("%i,%i, %f ", dx,dy, dx/dy);
		//col = create_trgb(255,(int)(1-(dx/maxh)*255),1 ,(int)((dx/maxh)*255));
		col = create_trgb(255,((1-(dy/maxw))*255),1 ,((dy/maxw)*255));
		my_mlx_pixel_put(img, dx, dy, col);//,0x00FF0000);
		//printf("\n%f,%f,%f, %x ", dx, (dx/maxh), 1-(dx/maxh), col);
		printf("\n%f,%f,%f, %x ", dy, (dy/maxw), 1-(dy/maxw), col);
	}

/*/
	dy = sqrt(fabs(pow(r,2) - pow(-x + h, 2))) + k ;
	while(i--){	
		printf("\n%i, %i, %x", dx,  dy, col  );
		//col = create_trgb(1, dx/dy*255, 0, (1-(dx/dy))*255);
		col = create_trgb(100, 255, 0, 255);
		dx = sqrt(fabs(pow(r,2) - pow(-dy + k, 2)) ) + h ;
		dy = sqrt(fabs(pow(r,2) - pow(-dx + h, 2))) + k ;
		//printf("x:%f y:%f  " ,dx,  dy);}
		my_mlx_pixel_put(img, dx, dy, col);//,0x00FF0000);
	}
*/
}



int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	float	i;
	float	h;
	float	w;
	float	rh;
	float	rw;
	int		col;
	float	init;

	h = 1500;
	w = 1000;
	rw = 0;
	rh = 0;//1/rw;//(w/h);
	col = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, h, w, "Hello world!");
	img.img = mlx_new_image(mlx, h, w);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	init = sqrt((pow(h, 2) + pow(w, 2)))  ;
	/*/
	 * while (h > 0 && w > 0)
	{
		//ft_printf("\n%f, %f, %f, %f", h, w, rh, rw);
		col = create_trgb(1, i/init*255, 0, (1-(i/init))*255);
		//printf("\n%f, %f, %f, %x", i/init, 1-(i/init), rh, col );
		//my_mlx_pixel_put(&img, h, w, col);//,0x00FF0000);
		i = sqrt((pow(h, 2) + pow(w, 2)))  ;
		rh = sqrt(pow(i, 2) - pow(w, 2)) - (h/w)*1;
		rw = sqrt(pow(i, 2) - pow(h, 2)) - (w/h)*1;
		h = rh;
		w = rw;
	}
	*/

	draw_circle( h/2,w/2, w/2 - 30, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}



/*/
#include "mlx.h"
#include "libft.h"
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


int	main(void)
{
	void	*mlx;
	t_data	*img;
//	void	*mlx_win;

//	mlx = mlx_init();
//	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//	mlx_loop(mlx);

	mlx = mlx_init();
	img->img = mlx_new_image(&mlx, 920, 680);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
}
/*/
