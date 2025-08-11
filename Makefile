##
##
## EPITECH PROJECT, 2025
## raytracer (Raylib)
##

NAME = raytracer
CXX = g++
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

# Includes
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
			   -I$(SRC_DIR)/Builders \
			   -I$(SRC_DIR)/Factories \
			   -I$(SRC_DIR)/Editor

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(INCLUDE_DIRS) -I/usr/local/include -I/opt/homebrew/include

# Linker flags (simple and robust)
LDFLAGS =
ifeq ($(UNAME_S),Linux)
	LDFLAGS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lconfig++
else ifeq ($(UNAME_S),Darwin)
	# Add generic Homebrew locations first
	LDFLAGS += -L/usr/local/lib -L/opt/homebrew/lib \
			   -lraylib -lconfig++ \
			   -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
			   -framework CoreFoundation -framework CoreGraphics -framework Foundation -framework AppKit \
			   -lobjc
endif

# Sources/objects
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
# Exclude legacy SFML renderer if still present in tree
SRCS := $(filter-out $(SRC_DIR)/Renders/SFMLRenderer.cpp,$(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
OBJ_DIRS := $(sort $(dir $(OBJS)))

# Rules

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
RESET = \033[0m

.PHONY: all banner clean fclean re dirs

all: banner dirs $(NAME)

banner:
	@printf "$(CYAN)=================================================================================$(RESET)\n"
	@printf "\n"
	@printf "$(MAGENTA)  ██████   █████  ██    ██     ████████ ██████   █████   ██████ ███████ ██████$(RESET)\n"
	@printf "$(MAGENTA)  ██   ██ ██   ██  ██  ██         ██    ██   ██ ██   ██ ██      ██      ██   ██$(RESET)\n"
	@printf "$(MAGENTA)  ██████  ███████   ████          ██    ██████  ███████ ██      █████   ██████$(RESET)\n"
	@printf "$(MAGENTA)  ██   ██ ██   ██    ██           ██    ██   ██ ██   ██ ██      ██      ██   ██$(RESET)\n"
	@printf "$(MAGENTA)  ██   ██ ██   ██    ██           ██    ██   ██ ██   ██  ██████ ███████ ██   ██$(RESET)\n"
	@printf "\n"
	@printf "$(CYAN)                          RayTracer build (Raylib edition)     $(RESET)\n"
	@printf "\n"
	@printf "$(CYAN)=================================================================================$(RESET)\n"

dirs:
	@for dir in $(OBJ_DIRS); do mkdir -p $$dir; done

$(NAME): $(OBJS)
	@printf "$(GREEN)Linking$(RESET) %s\n" "$(NAME)"
	@$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@printf "$(GREEN)Build success:$(RESET) %s\n" "$(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)Compiling$(RESET) %s\n" "$<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(RED)Cleaning binary and outputs...$(RESET)\n"
	@rm -f $(NAME) output.ppm output.png

re: fclean all