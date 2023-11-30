CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pf_libft.a
SRC = src/ft_atoi.c src/ft_bzero.c src/ft_calloc.c src/ft_cjoin.c src/ft_dupnfree.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c src/ft_itoa.c src/ft_llitoahex.c src/ft_lstadd_back.c src/ft_lstadd_front.c src/ft_lstclear.c src/ft_lstdelone.c src/ft_lstiter.c src/ft_lstlast.c src/ft_lstmap.c src/ft_lstnew.c src/ft_lstsize.c src/ft_memccpy.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c src/ft_parse_num.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strdup.c src/ft_strdupchar.c src/ft_strdupm.c src/ft_striteri.c src/ft_strjoin.c src/ft_strjoinfree.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_strtrim.c src/ft_strupp.c src/ft_substr.c src/ft_substrfree.c src/ft_tolower.c src/ft_toupper.c src/ft_uitoa.c src/ft_uitoahex.c src/pf_flags_execution.c src/pf_ft_printf.c src/pf_parse_format.c src/pf_triglist_utils.c
OBJ = $(SRC:src/%.c=objects/%.o)
AR = ar rc
RAN = ranlib 
OBJDIR = objects

DEF_COLOR 	:= \033[0;39m
GRAY 		:= \033[0;90m
RED 		:= \033[0;91m
GREEN 		:= \033[0;92m
YELLOW 		:= \033[0;93m
BLUE 		:= \033[0;94m
MAGENTA 	:= \033[0;95m
CYAN 		:= \033[0;96m
WHITE 		:= \033[0;97m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Making library : $(NAME)"
	@printf "$(MAGENTA)"
	@$(AR) $(NAME) $(OBJ)
	@$(RAN) $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: src/%.c
	@printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR)/$(OBJ) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean:
	@rm -rf $(OBJDIR)/$(OBJ) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"
	@rm -f $(NAME)
	@printf "$(RED)Library deleted !$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re 
