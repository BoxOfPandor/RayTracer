##
## EPITECH PROJECT, 2025
## OOP
## File description:
## raytracer
##

NAME = raytracer
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Detect OS
UNAME_S := $(shell uname -s)

# SFML flags
ifeq ($(UNAME_S),Darwin)
    # macOS specific SFML flags
    SFML_LIBS = -L/opt/homebrew/opt/sfml@2/lib -lsfml-graphics -lsfml-window -lsfml-system
    SFML_INCLUDES = -I/opt/homebrew/opt/sfml@2/include
else
    # Linux SFML flags
    SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
    SFML_INCLUDES =
endif

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIRS = -I$(SRC_DIR) \
               -I$(SRC_DIR)/Math \
               -I$(SRC_DIR)/RayTracer \
               -I$(SRC_DIR)/Primitives \
               -I$(SRC_DIR)/Materials \
               -I$(SRC_DIR)/Lights \
               -I$(SRC_DIR)/Renders \
               -I$(SRC_DIR)/SceneLoaders \
               $(SFML_INCLUDES)

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
OBJ_DIRS := $(sort $(dir $(OBJS)))

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

.PHONY: all clean fclean re run dirs sources

all: dirs $(NAME)

dirs:
	@for dir in $(OBJ_DIRS); do \
		mkdir -p $$dir; \
	done

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)
	@echo "$(GREEN)$(NAME) successfully compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@rm -f output.ppm output.png
	@echo "$(RED)Fully cleaned!$(RESET)"

re: fclean all

sources:
	@echo "$(YELLOW)Sources détectées:$(RESET)"
	@for src in $(SRCS); do \
		echo "$$src"; \
	done
