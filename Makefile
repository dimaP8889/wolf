NAME = wolf3d

FILES = main 

SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(FILES)))

CC = gcc

LIB_SRC = $(shell find libft | fgrep ".c")

CGFLAGS = -framework OpenGL -framework AppKit

INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

HEADER = -I./includes -I./libft/includes


FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB_SRC) $(OBJ)
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(CGFLAGS) $(FRAMEWORKS) libft/libft.a
	@echo "Good"

obj/%.o: src/%.c
	@$(CC) -o $@ $(FLAGS) $(HEADER) $(INCLUDES) -c $^

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "Object files deleted: $(NAME)"

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@echo "Executable file deleted: libft/libft.a"
	@echo "Executable file deleted: $(NAME)"

re: fclean all