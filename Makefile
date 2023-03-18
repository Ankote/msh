NAME = minishell

CC = cc
DIR = builtins
PRC = parcing
CFLAGS = -Wall -Wextra -Werror

FILES = minishell.c  $(PRC)/handle_quotes.c $(PRC)/utils/utils0.c\
		$(PRC)/utils/utils1.c $(PRC)/lexer.c $(PRC)/expanding.c\
		$(PRC)/utils/lexer_utils.c $(DIR)/echo.c $(DIR)/exit.c\
		$(PRC)/errors/errors.c $(PRC)/here_doc.c

OBJCS = $(FILES:.c=.o)

INCLUDES = libft/libft.a get_next_line/get_next_line.a #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJCS)
	@echo "\n"
	@make -C libft
	@make -C get_next_line
	@echo "\033[0;32mCompiling minishell..."
	@$(CC)  $(OBJCS) -lreadline  $(CFLAGS) $(INCLUDES) -o $(NAME)

	@echo "\n\x1b[34mDone !\033[0m"
%.o:%.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@$(CC)  $(CFLAGS)  -c $<  -o $@

clean :
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@make clean -C get_next_line/
	@echo "\nRemoving binaries..."
	@rm -fr $(OBJCS)
	@echo "\033[0;31m𝑶𝒃𝒋𝒆𝒄𝒕𝒔' 𝒄𝒍𝒆𝒂𝒏𝒆𝒅\033[0m"
	@echo "\033[0m"

fclean : clean
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@make fclean -C get_next_line/
	@echo "\nDeleting objects..."
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re :fclean all

run : re clean 
	clear
	@./minishell
	

push :
	git add .
	git commit -m "Updated"
	git push