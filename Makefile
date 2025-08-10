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
			   -I$(SRC_DIR)/Factories

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
.PHONY: all clean fclean re dirs

all: dirs $(NAME)

dirs:
	@for dir in $(OBJ_DIRS); do mkdir -p $$dir; done

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) output.ppm output.png

re: fclean all
	@echo "LIBCONFIG_PKGCONFIG=$(LIBCONFIG_PKGCONFIG)"
	@echo "HOMEBREW_PREFIX=$(HOMEBREW_PREFIX)"
	@echo "RAYLIB_CFLAGS=$(RAYLIB_CFLAGS)"
	@echo "RAYLIB_LDFLAGS=$(RAYLIB_LDFLAGS)"
	@echo "LIBCONFIG_CFLAGS=$(LIBCONFIG_CFLAGS)"
	@echo "LIBCONFIG_LDFLAGS=$(LIBCONFIG_LDFLAGS)"
	@echo "RPATH_FLAGS=$(RPATH_FLAGS)"