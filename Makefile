CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex.a
SRC = src/execute.c src/file_access.c src/ft_mstrjoin.c src/main.c src/parse_command.c src/parse_files.c src/free_manager.c
HSRC = .
OBJ = $(SRC:src/%.c=objects/%.o)
AR = ar rc
RAN = ranlib 
OBJDIR = objects

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

$(NAME): makepf cOBJ pipex $(OBJ)
	@echo "$(GREEN)Making library : $(NAME)"
	@printf "$(MAGENTA)"
	@$(AR) $(NAME) $(OBJDIR)/*
	@$(RAN) $(NAME)
	@rm /tmp/log.txt;
	@printf "Done !$(DEF_COLOR)\n"

cOBJ:
	@clear
	@echo "$(CYAN)Creating 'objects' directory$(DEF_COLOR)"
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi;
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o: src/%.c
	@make -n | grep "$<" >> /tmp/log.txt; \
	len=$$(grep -c "cc -Wall" /tmp/log.txt); \
	total=$$(echo src/*.c | wc -w); \
	printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s $(GREEN)%d$(GRAY)/$(RED)%d\n' "$<" "$@" "$$len" "$$total";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	rm -f $(NAME)
	@printf "$(RED)Library deleted !$(DEF_COLOR)\n"

makepf:
	make -C pf_libft/
	cp pf_libft/pf_libft.a pipex.a

pipex:
	@echo "\n_______  _____  _______  ________  ____  ____  "
	@echo "|_   __ \|_   _||_   __ \|_   __  ||_  _||_  _| "
	@echo "| |__) | | |    | |__) | | |_ \_|  \ \  / /   "
	@echo "  |  ___/  | |    |  ___/  |  _| _    | ||    "
	@echo " _| |_    _| |_  _| |_    _| |__/ | _/ /'\ \_  "
	@echo "|_____|  |_____||_____|  |________||____||____| \n"                                               

re: fclean all

.PHONY: all clean fclean re bonus
