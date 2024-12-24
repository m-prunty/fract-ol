################################################################################
#                                     CONFIG                                   #
################################################################################
NAME		:= fractol 
LIBFT  		:= ./libft
LIBFT_LIB	:= $(LIBFT)/libft.a
MLIBX		:= minilibx-linux
MLIBX_LIB	:= $(MLIBX)/libmlx.a

LDFLAGS 	:= -L$(LIBFT) -lft -L$(MLIBX) -lmlx
INCLUDE		:= -I$(LIBFT)/include -Iinclude -I$(MLIBX)
FLAGS	 	:= -Wall -Wextra -Werror -g
SRCDIR		:= src
OBJDIR		:= obj

XLIBS		:= -lXext -lX11 -lm -lz 

CC			:= gcc $(FLAGS) $(INCLUDE) 
################################################################################
#                                     COLOURS                                  #
################################################################################
CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN	 	:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN		:= \033[1;36m
PURPLE		:= \033[1;35m
BOLD		:= \033[1m
################################################################################
#	                          SOURCE & OBJECT FILES                            #
################################################################################
SRC   		:= $(wildcard $(SRCDIR)/*.c)
OBJECTS	:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

ALL_OBJS := $(OBJECTS)

################################################################################
#                                 PROGRESS BAR                                 #
################################################################################

# Create a simpler compiler string for the dry run
COMP_CHECK := gcc $(FLAGS) $(INCLUDE) -c

# Count files that will actually need recompilation
# TOTAL_FILES = $(shell $(MAKE) -n $(ALL_OBJS) 2>/dev/null | grep -o "$(CC).*\.c" | wc -l)
# Get list of files that will actually be recompiled
# TOTAL_FILES = $(shell $(MAKE) -n $(ALL_OBJS) 2>/dev/null | grep -o "$(CC).*\.c" | wc -l)
# TOTAL_FILES = $
TOTAL_FILES	:= $(words $(ALL_OBJS))
CURR_FILE 	:= 0

define progress_bar
$(eval CURR_FILE = $(shell expr $(CURR_FILE) + 1))
@printf "\r$(CYAN)⌛ [%-50s] %d/%d files - Compiling: $<$(CLR_RMV)\n" \
    "$$(printf '#%.0s' $$(seq 1 $$(expr $(CURR_FILE) \* 50 / $(TOTAL_FILES))))" \
    $(CURR_FILE) $(TOTAL_FILES)
endef

################################################################################
#                                COMPILATION                                   #
################################################################################
all: check-and-reinit-submodules $(LIBFT_LIB) $(MLIBX_LIB) banner $(NAME)

$(NAME):  $(ALL_OBJS)
	@$(CC) $^  $(LDFLAGS) $(XLIBS) -o $@ 
	@printf "\n$(GREEN)✨ $(NAME) compiled successfully!$(CLR_RMV)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC)  -c $< -o $@
	$(call progress_bar)

$(LIBFT_LIB):
	@printf "$(BLUE)📚 Building $(LIBFT)...$(CLR_RMV)\n"
	@make -C $(LIBFT)
	@printf "$(GREEN)✓ Libft ready!$(CLR_RMV)\n"

$(MLIBX_LIB):
	@printf "$(BLUE)📚 Building $(MLIBX)...$(CLR_RMV)\n"
	@make -C $(MLIBX)
	@printf "$(GREEN)✓ Minilibx ready!$(CLR_RMV)\n"

banner:
	@printf "%b" "$(PURPLE)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                      Building fractol                         ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@printf "%b" "$(CLR_RMV)"

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-+]'; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init; \
		fi

clean:
	@printf "$(RED)🧹 Cleaning object files...$(CLR_RMV)\n"
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)✓ Clean complete!$(CLR_RMV)\n"

fclean: clean
	@printf "$(RED)🗑️  Removing executables...$(CLR_RMV)\n"
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@printf "$(GREEN)✓ Full clean complete!$(CLR_RMV)\n"

re: fclean all

.PHONY: all clean fclean re banner progress_bar 
	################################################################################
	#                                     END                                      #
	################################################################################


