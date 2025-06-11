# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -L$(LIBFTDIR) -lft -lreadline
INCLUDES = -Iinclude 

# Directories
SRCDIR = src
OBJDIR = objects
INCDIR = include
LIBFTDIR = include/libft
LIBFT = $(LIBFTDIR)/libft.a

# Source files and object files
SRCS = $(SRCDIR)/minish.c
SRCS += $(SRCDIR)/error/error.c
SRCS += $(SRCDIR)/expansion/append_char.c
SRCS += $(SRCDIR)/expansion/append_exit_code.c
SRCS += $(SRCDIR)/expansion/append_variable.c
SRCS += $(SRCDIR)/expansion/check_quotes.c
SRCS += $(SRCDIR)/expansion/expansion.c
SRCS += $(SRCDIR)/free/free_expansion.c
SRCS += $(SRCDIR)/free/free_parsing.c
SRCS += $(SRCDIR)/init/get_envp.c
SRCS += $(SRCDIR)/init/get_pwd.c
SRCS += $(SRCDIR)/init/init_banner.c
SRCS += $(SRCDIR)/init/init_minish.c
SRCS += $(SRCDIR)/init/init_parsing.c
SRCS += $(SRCDIR)/init/init_signals.c
SRCS += $(SRCDIR)/init/init_token.c
SRCS += $(SRCDIR)/parser/add_command.c
SRCS += $(SRCDIR)/parser/add_pipe.c
SRCS += $(SRCDIR)/parser/add_redirect.c
SRCS += $(SRCDIR)/parser/get_token_type.c
SRCS += $(SRCDIR)/parser/get_token.c
SRCS += $(SRCDIR)/parser/handle_heredoc.c
SRCS += $(SRCDIR)/parser/open_file.c
SRCS += $(SRCDIR)/parser/parser.c
SRCS += $(SRCDIR)/parser/quotes.c
SRCS += $(SRCDIR)/parser/skip_whitespaces.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Output executable
NAME = minish

# Colors for output
GREEN		=	\033[0;32m
ORANGE	=	\033[38;5;214m
GRAY		=	\033[0;90m

# Rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GRAY)building minish..."
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCDIR) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) has been created successfully"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

$(LIBFT):
	@echo "$(GRAY)building libft..."
	@make -C $(LIBFTDIR) > /dev/null
	@echo "$(GREEN)libft has been created successfully"

clean:
	@echo "$(ORANGE)removing object files..."
	@rm -rf $(OBJDIR)
	@echo "$(ORANGE)objects have been removed"

fclean: clean
	@echo "$(ORANGE)removing $(NAME)..."
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean > /dev/null
	@echo "$(ORANGE)$(NAME) has been removed"

re: fclean all

.PHONY: all clean fclean re
