# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvitale <lvitale@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 14:40:03 by jhouyet           #+#    #+#              #
#    Updated: 2024/04/19 11:53:30 by lvitale          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m 

NAME		= philo

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= include/

SRC 		= 	$(SRC_DIR)main.c \
				$(SRC_DIR)actions.c \
				$(SRC_DIR)manager.c \
				$(SRC_DIR)utils.c \


OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			= gcc
RM			= rm -f
C_FLAGS		= -Wall -Wextra -Werror
INCS 		= -I$(INC_DIR)

TOTAL_FILES 	:= $(words $(SRC))
CURRENT_FILE 	:= 0

define progress_bar_philo
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "\r$(YELLOW)Compiling Philo... [%-$(TOTAL_FILES)s] %d/%d $(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	$(call progress_bar_philo)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking objects to create executable...$(NC)"
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(BLUE)Executable $(NAME) created!$(NC)"

clean:
	@echo "$(ORANGE)Cleaning objects for Philo...$(NC)"
	@$(RM) $(OBJ_DIR)*.o
	@echo "$(GREEN)Cleaned Philo objects!$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(BLUE)Fully cleaned Philo!$(NC)"

re: fclean all

.PHONY: all clean fclean re