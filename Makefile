CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror
NAME 		:= pipex
PF_LIBFT 	:= pf_libft/pf_libft.a
AR 			:= ar rc
RAN 		:= ranlib 
OBJDIR 		:= objects
SRC 		:= src/parse_utils.c src/main.c src/parse_command.c \
			   src/parse_files.c src/free_manager.c src/errors.c src/parse_utils_2.c \
			   src/here_doc.c src/checks.c
OBJ 		:= $(SRC:src/%.c=objects/%.o)

DEF_COLOR 	:= \033[0;39m
MAGENTA 	:= \033[0;95m
GRAY 		:= \033[0;90m
RED 		:= \033[0;91m
GREEN 		:= \033[0;92m
YELLOW 		:= \033[0;93m
BLUE 		:= \033[0;94m
CYAN 		:= \033[0;96m
WHITE 		:= \033[0;97m

all: $(NAME)

$(NAME): $(PF_LIBFT) $(OBJ)
	@echo "$(GREEN)Making executable : $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) $(PF_LIBFT) -o $(NAME)
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: src/%.c
	@printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s\n' "$<" "$@";
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:	
	@make -C pf_libft/ clean
	@rm -rf $(OBJDIR)/$(OBJ)
	@printf "$(RED)Objects deleted.$(DEF_COLOR)\n"

fclean:
	@make -C pf_libft/ fclean
	@rm -rf $(OBJDIR)/$(OBJ)
	@rm -rf $(NAME)
	@printf "$(RED)Objects deleted.$(DEF_COLOR)\n"

$(PF_LIBFT):
	@make -C pf_libft/

re: fclean all

.PHONY: all clean fclean re bonus
