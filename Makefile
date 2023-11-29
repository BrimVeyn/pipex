CC := cc
CFLAGS := -Wall -Wextra -Werror
LIB := pipex.a
PROGRAM := pipex
SRC = src/file_access.c src/parse_utils.c src/main.c src/parse_command.c \
	  src/parse_files.c src/free_manager.c src/errors.c src/parse_utils_2.c
OBJ = $(SRC:src/%.c=objects/%.o)
AR := ar rc
RAN := ranlib 
OBJDIR := objects

DEF_COLOR 	:= \033[0;39m
MAGENTA 	:= \033[0;95m
GRAY 		:= \033[0;90m
RED 		:= \033[0;91m
GREEN 		:= \033[0;92m
YELLOW 		:= \033[0;93m
BLUE 		:= \033[0;94m
CYAN 		:= \033[0;96m
WHITE 		:= \033[0;97m

all: $(LIB)

$(LIB): makepf print_pipex $(OBJ)
	@echo "$(GREEN)Making library : $(LIB)"
	@printf "$(MAGENTA)"
	@$(AR) $(LIB) $(OBJ)
	@$(RAN) $(LIB)
	@echo "$(GREEN)Making executable : $(PROGRAM)"
	@$(CC) $(CFLAGS) $(LIB) -o $(PROGRAM)
	@rm /tmp/log.txt;
	@printf "Done !$(DEF_COLOR)\n"

$(OBJDIR)/%.o: src/%.c
	@make -n | grep "$<" >> /tmp/log.txt; \
	len=$$(grep -c "cc -Wall" /tmp/log.txt); \
	total=$$(echo src/*.c | wc -w); \
	printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s $(GREEN)%d$(GRAY)/$(RED)%d\n' "$<" "$@" "$$len" "$$total";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:	
	@make -C pf_libft/ clean
	@rm -rf $(OBJDIR)/$(OBJ)
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@make -C pf_libft/ fclean
	@rm -f $(LIB)
	@printf "$(RED)Library deleted !$(DEF_COLOR)\n"

makepf:
	make -C pf_libft/
	cp pf_libft/pf_libft.a pipex.a

print_pipex:
	@echo "\n_______  _____  _______  ________  ____  ____  "
	@echo "|_   __ \|_   _||_   __ \|_   __  ||_  _||_  _| "
	@echo "| |__) | | |    | |__) | | |_ \_|  \ \  / /   "
	@echo "  |  ___/  | |    |  ___/  |  _| _    | ||    "
	@echo " _| |_    _| |_  _| |_    _| |__/ | _/ /'\ \_  "
	@echo "|_____|  |_____||_____|  |________||____||____| \n"                                               

re: fclean all

.PHONY: all clean fclean re bonus
