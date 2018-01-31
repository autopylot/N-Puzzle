# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 14:32:32 by wlin              #+#    #+#              #
#    Updated: 2018/01/26 16:14:47 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
BLUE="\x1b[34m"
MAGENTA="\x1b[35m"
CYAN="\x1b[36m"
RESET="\x1b[0m"

# Executeable
NAME = n_puzzle

# Compiler and flags
CXX = g++
CPPFLAGS = -Werror -Wall -Wextra

# Folders
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include

# Sources and objects
SRCS = \

OBJS = $(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRCS)))

INCLUDE = $(addprefix -I, $(INC_DIR))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "\033[32mExecutable \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(BUILD)/%.o: %.cpp %.hpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<




.PHONY: all clean fclean re build

build:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(OBJS);

fclean: clean
	@rm -f $(NAME)

re: fclean all
