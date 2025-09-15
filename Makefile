# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
INCLUDES = -Iinclude -Iinclude/libft/include
LIBS = -Linclude/libft -lft

# Directories
SRCDIR = src
OBJDIR = objects
INCDIR = include
LIBFTDIR = include/libft
LIBFT = $(LIBFTDIR)/libft.a

# Find all .c files in src and subdirectories
SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Output executable
NAME = minishell

# Colors for output
CLOVER   = \033[38;2;120;200;80m
ORANGE  = \033[38;5;214m
GRAY    = \033[0;90m

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GRAY)building minishell..."
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME) -lreadline
	@echo "$(CLOVER)$(NAME) has been created successfully."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GRAY)building libft..."
	@make -C $(LIBFTDIR) > /dev/null
	@echo "$(CLOVER)libft has been created successfully."

clean:
	@echo "$(ORANGE)cleaning object files..."
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean > /dev/null
	@echo "$(ORANGE)objects have been removed."

fclean: clean
	@echo "$(ORANGE)removing $(NAME)..."
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean > /dev/null
	@echo "$(ORANGE)$(NAME) has been removed."

re: fclean all

.PHONY: all clean fclean re
