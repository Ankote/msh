NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

FILES = minishell.c  parcing/handle_quotes.c parcing/utils/utils0.c\
		parcing/utils/utils1.c parcing/lexer.c parcing/expanding.c\
		parcing/utils/lexer_utils.c\
		
		

OBJCS = $(FILES:.c=.o)

INCLUDES = libft/libft.a

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