NAME = minishell

CC = cc
DIR = builtins
PRC = parcing
CFLAGS = -Wall -Wextra -Werror

FILES = minishell.c  $(PRC)/handle_quotes.c $(PRC)/utils/utils0.c\
		$(PRC)/utils/utils1.c $(PRC)/lexer.c $(PRC)/expanding.c\
		$(PRC)/utils/lexer_utils.c $(DIR)/echo.c $(DIR)/exit.c\
		$(PRC)/errors/errors.c

OBJCS = $(FILES:.c=.o)

INCLUDES = libft/libft.a -fsanitize=address

all : $(NAME)
	clear

$(NAME) : $(OBJCS)
	@make -C libft
	@$(CC)  $(OBJCS) -lreadline  $(CFLAGS) $(INCLUDES) -o $(NAME)

%.o:%.c
	@$(CC)  $(CFLAGS)  -c $<  -o $@

clean :
	@rm -fr libft/*.o && rm -fr libft/*.a
	@rm -fr $(OBJCS)
	@echo "\033[0;31m𝑶𝒃𝒋𝒆𝒄𝒕𝒔' 𝒄𝒍𝒆𝒂𝒏𝒆𝒅\033[0m"
	clear

fclean : clean
	@rm -fr $(NAME)
	@echo "\033[1;33m𝙀𝙫𝙚𝙧𝙮𝙩𝙝𝙞𝙣𝙜'𝙨 𝙘𝙡𝙚𝙖𝙣𝙚𝙙\033[0m"
	clear

re :fclean all

run : re clean
	@./minishell
push :
	git add .
	git commit -m "Updated"
	git push