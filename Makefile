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
CPPFLAGS = -Werror -Wall -Wextra -O3

# Folders
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include

# Sources and objects
SRCS = main.cpp \
Astar.cpp \
Heuristic.cpp \
N_puzzle.cpp \
Puzzle.cpp 

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:%=%.o)))

INCLUDE = $(addprefix -I, $(INC_DIR))

all: $(NAME)

$(NAME):
	@g++ -Wall -Wextra -Werror -O3 -o $(NAME) ./src/main.cpp ./src/Astar.cpp ./src/Heuristic.cpp ./src/N_puzzle.cpp ./src/Puzzle.cpp
	@echo "\033[32mExecutable \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

.PHONY: all clean fclean re build

fclean:
	@rm -f $(NAME)

re: fclean all
