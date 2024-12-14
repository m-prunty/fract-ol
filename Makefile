NAME = fractol 
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -g -I${INC} #-Werror 
LIB = libft
MLIBX = mlx
INCXLIBS = -lXext -lX11 -lm -lz 
INC = include
SRC_DIR	= src
OBJ_DIR	= obj

SRC_FILES = ${wildcard $(SRC_DIR)/*.c}

all:	$(NAME)
	@echo ${SRC_FILES} ${OBJ}


$(NAME): 
		@cd $(LIB) && $(MAKE) 
		 $(CC) $(CFLAGS) $(SRC_FILES) -o $(NAME)  -L$(MLIBX) -l$(MLIBX) -L$(LIB) -Wl,-rpath=$(LIB) -lft $(INCXLIBS)

clean:
		@cd libft && $(MAKE) clean
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(LIB).so
		$(RM) $(NAME)

re: fclean all
