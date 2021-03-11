### COMPILATION ###
C      = gcc
FLAGS  = -Wall -Wextra -Werror

### EXECUTABLE ###
NAME   = fdf

### INCLUDES ###
LIBFT  = libft
OBJ_PATH  = obj
INC = include
SRC_PATH  = src

### SOURCES ###
SOURCES = main.c				\
			bresenham.c			\
			ft_altitude.c		\
			ft_table_dbl.c		\
			int_tab_dup.c		\
			center_map.c		\
			ft_button.c			\
			ft_table_int.c		\
			dbl_tab_dup.c		\
			ft_display_map.c	\
			ft_translation.c	\
			projections.c		\
			deal_events.c		\
			ft_free.c			\
			ft_trunc_hexa.c		\
			test_line.c			\
			events.c			\
			ft_parse_map.c		\
			ft_zoom.c			\
			fields_definition.c	\
			ft_rotations.c		\
			ft_color.c

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: obj_dir $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Creating library$(NOC)"
	@echo "$(CYAN)  Generating library objects$(NOC)"
	@make -C $(LIBFT)
	@echo "$(CYAN)  Generating fdf program objects$(NOC)"
	@$(CC) $(FLAGS) -L $(LIBFT) -lft -o $@ $(OBJS) -framework OpenGL -framework AppKit -lmlx
	@echo "$(RED)FDF successfully compiled$(NOC)"

obj_dir:
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/$(NAME).h
	@echo "  $(GREEN)[$(CC) - $(FLAGS)]$(NOC) $(YELLOW)in progress ...: $(WHITE)$(notdir $^) $(RED)->$(NOC) $(notdir $@)"
	@$(CC) $(FLAGS) -I $(INC) -c -o $@ $<

norme :
	@echo "$(CYAN)Does the fdf source files are normed ?$(NOC)"
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@echo "$(CYAN)Does the header files are normed ?$(NOC)"
	@norminette -R CheckForbiddenSourceHeader $(INC)
	@echo "$(CYAN)Does the library files are normed ?$(NOC)"
	@make norme -C $(LIBFT)

clean:
	@echo "$(CYAN)Supressing libraries objects$(NOC)"
	@make clean -C $(LIBFT)
	@echo "$(RED)  Libraries objects destroyed$(NOC)"
	@echo "$(CYAN)Supressing fdf objects$(NOC)"
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)  Fdf objects destroyed$(NOC)"

fclean: clean
	@echo "$(CYAN)Supressing fdf binary & static library$(NOC)"
	@make fclean -C $(LIBFT)
	@echo "$(RED)  Static library destroyed$(NOC)"
	@rm -f $(NAME)
	@echo "$(RED)  Fdf binary destroyed$(NOC)"

re: fclean
	@$(MAKE) all -j

.PHONY: re, fclean, clean, obj_dir, norme
