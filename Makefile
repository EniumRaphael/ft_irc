# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+         #
#    Created: 2023/11/12 11:05:05 by rparodi           #+#    #+#              #
#    Updated: 2025/05/02 15:40:00 by rparodi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

# Name
NAME = ircserv

# Commands
CXX = c++
RM = rm -rf

# Flags
#  Mandatory flags for 42
CXXFLAGS = -Werror -Wextra -Wall -std=c++98
#  Flags to have the dependences (can be removed for correction)
#  Flags to have the debug (can be removed for correction)
DEBUG = -g3
# DEBUG += -fsanitize=address
CXXFLAGS += $(DEBUG)

# Sources
SRC = main.cpp

INC_DIR =

CPPFLAGS = $(addprefix -I, $(INC_DIR)) -MMD -MP

#  Flags to have the dependences (can be removed for correction)
# DEBUG = -g3
# CPPFLAGS += $(DEBUG)

# Objects
OBJDIRNAME = ./build
OBJ = $(addprefix $(OBJDIRNAME)/,$(SRC:.cpp=.o))

# Colors
GREEN = \033[32m
GREY = \033[0;90m
RED = \033[0;31m
GOLD = \033[38;5;220m
END = \033[0m

# Rules

# All (make all)
all: header $(NAME) footer

# Clean (make clean)
clean:
	@printf '$(GREY) Removing $(END)$(RED)Objects$(END)\n'
	@printf '$(GREY) Removing $(END)$(RED)Objects Folder$(END)\n'
	@$(RM) $(OBJDIRNAME)

# Clean (make fclean)
fclean: clean
	@printf '$(GREY) Removing $(END)$(RED)Program$(END)\n'
	@$(RM) $(NAME)
	@echo ""

# Restart (make re)
re: header fclean all

# Dependences for all
$(NAME): $(OBJ)
	@mkdir -p $(OBJDIRNAME)
	@printf '$(GREY) Creating $(END)$(GREEN)$(OBJDIRNAME)$(END)\n'
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJ)

# Creating the objects
$(OBJDIRNAME)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@printf '$(GREY) Compiling $(END)$(GREEN)$<$(END)\n'
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

debug: CPPFLAGS += -D DEBUG=1
debug: re

test: debug
	@printf '$(GREY) now running with\n\t- Port:\t$(GREEN)4243$(GREY)\n\t-Password:\t$(GREEN)irc$(END)\n'
	@./$(NAME) 4243 irc

#	Header
header:
		@clear
		@printf '\n\n'
		@printf '$(GOLD)            *******     ****** ******* $(END)\n'
		@printf '$(GOLD)          ******        ***    ******* $(END)\n'
		@printf '$(GOLD)      *******           *      ******* $(END)\n'
		@printf '$(GOLD)     ******                  ******* $(END)\n'
		@printf '$(GOLD)  *******                  ******* $(END)\n'
		@printf '$(GOLD) *******************    *******      * $(END)\n'
		@printf '$(GOLD) *******************    *******    *** $(END)\n'
		@printf '$(GOLD)              ******    ******* ****** $(END)\n'
		@printf '$(GOLD)              ******  $(END)\n'
		@printf '$(GOLD)              ******  $(END)\n'
		@printf '$(GREY)                                      Made by rparodi$(END)\n\n'

#	Footer
footer:
		@printf "\n"
		@printf "$(GOLD)                   ,_     _,$(END)\n"
		@printf "$(GOLD)                   | \\___//|$(END)\n"
		@printf "$(GOLD)                   |=6   6=|$(END)\n"
		@printf "$(GOLD)                   \\=._Y_.=/$(END)\n"
		@printf "$(GOLD)                    )  \`  (    ,$(END)\n"
		@printf "$(GOLD)                   /       \\  (('$(END)\n"
		@printf "$(GOLD)                   |       |   ))$(END)\n"
		@printf "$(GOLD)                  /| |   | |\\_//$(END)\n"
		@printf "$(GOLD)                  \\| |._.| |/-\`$(END)\n"
		@printf "$(GOLD)                   '\"'   '\"'$(END)\n"
		@printf '              $(GREY)The compilation is$(END) $(GOLD)finish$(END)\n               $(GREY)Have a good $(END)$(GOLD)correction !$(END)\n'

clangd:
	@printf "CompileFlags:\n" > ./.clangd
	@printf "  Add:\n" >> ./.clangd
	@printf "    - \"-xc++\"\n" >> ./.clangd
	@for FLAG in $(CXXFLAGS); do \
		printf "    - \"$$FLAG\"\n" >> ./.clangd; \
	done
	@printf "    - \"-I"$(shell pwd)"/\"\n" >> .clangd;
	@for file in $(INC_DIR); do \
		printf "    - \"-I"$(shell pwd)"/"$$file"\"" >> .clangd; \
	done
	@printf "\n" >> ./.clangd
	@printf '$(GREY) Now parsing settings is set in $(END)$(GREEN)./.clangd$(END)\n'

#	Phony
.PHONY: all clean fclean re clangd debug test
-include	${OBJ:.o=.d}
