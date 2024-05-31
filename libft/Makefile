NAME = libft
FLAGS = -Wall  -Werror -Wextra  
SRC = ${wildcard ft_*.c}
BSRC = ${wildcard $(BONUSDIR)/ft_*.c}
PSRC = ${wildcard $(PRINTDIR)/ft_*.c}
BONUSDIR = bonus
PRINTDIR = ft_printf
SOLIB =  lib 

#OBJ = $(patsubst  *.c, *.o, $(SRC))
# ft_strrchr.c, ft_calloc.c, ft_isalnum.c, ft_strlcat.c, ft_strmapi.c, libft.h, ft_strchr.c, ft_isprint.c, ft_strtrim.c, ft_isascii.c, ft_strncmp.c, ft_memcmp.c, ft_tolower.c, ft_split.c, ft_putstr_fd.c, ft_isdigit.c, ft_substr.c, ft_putnbr_fd.c, ft_toupper.c, ft_memmove.c, ft_memcpy.c, ft_strlen.c, ft_strnstr.c, ft_strlcpy.c, ft_atoi.c, ft_memchr.c, ft_putchar_fd.c, ft_memset.c, ft_putendl_fd.c, ft_itoa.c, ft_strjoin.c, ft_bzero.c, ft_strdup.c, ft_striteri.c, ft_isalpha.c
#BONUS = $(patsubst  *.c, *.o, $(BSRC))
#ft_lstnew.c, ft_lstdelone.c, ft_lstclear.c, ft_lstadd_front.c, ft_lstadd_back.c, ft_lstsize.c, ft_lstiter.c, ft_lstmap.c, ft_lstlast.c
#PRINT = $(patsubst  *.c, *.o, $(PSRC))

CC = cc

##all:	${NAME} 

all: bonus print ${NAME}  
	${MAKE} so
	${MAKE} clean 

#	@cp ${NAME}.so ${SOLIB}

bonus:
	@cp libft.h $(BONUSDIR)
	gcc ${FLAGS} -c ${BSRC}
	ar rcs ${BONUSDIR}.apt *.o

print: 
	@cp libft.h $(PRINTDIR)
	gcc ${FLAGS} -c ${PSRC}
	ar rcs ${PRINTDIR}.apt *.o

${NAME}:
	gcc ${FLAGS} -c ${SRC}
	ar rcs ${NAME}.a *.o

so:	
	gcc -shared -o libft.so -Wl,--whole-archive ${wildcard *.a} -Wl,--no-whole-archive ${wildcard *.apt} 
##$(CC) -nostartfiles -fPIC $(FLAGS) $(SRC)
##gcc -nostartfiles -shared -o libft.so $(OBJ) 
##${clean}

clean::
	rm -f *.o

fclean: clean
	rm -f *.a *.apt *.so

re:	fclean all

.PHONY : all all_so clean fclean re so bonus print 
	
