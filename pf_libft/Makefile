CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pf_libft.a
SRC = $(wildcard src/*.c)
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

$(NAME): cOBJ $(OBJ)
	@echo "$(GREEN)Making library : $(NAME)"
	@printf "$(MAGENTA)"
	@$(AR) $(NAME) $(OBJDIR)/*
	@$(RAN) $(NAME)
	@rm /tmp/log;
	@printf "Done !$(DEF_COLOR)\n"

cOBJ:
	@clear
	@echo "$(CYAN)Creating 'objects' directory$(DEF_COLOR)"
	@if [ -d $(OBJDIR) ]; then rm -rf $(OBJDIR); fi;
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o: src/%.c
	@make -n | grep "$<" >> /tmp/log; \
	len=$$(grep -c "cc -Wall" /tmp/log); \
	total=$$(echo src/*.c | wc -w); \
	printf '$(YELLOW)Compiling : %-25s $(CYAN)-->	$(YELLOW)%-30s $(GREEN)%d$(GRAY)/$(RED)%d\n' "$<" "$@" "$$len" "$$total";
	@printf "$(BLUE)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR) 
	@printf "$(RED)Objects deleted !$(DEF_COLOR)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)Library deleted !$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re bonus
