##
## EPITECH PROJECT, 2025
## OOP
## File description:
## raytracer
##

NAME = raytracer
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Detect raylib and libconfig via pkg-config, with Homebrew fallback on macOS
RAYLIB_PKGCONFIG := $(shell pkg-config --exists raylib && echo yes || echo no)
LIBCONFIG_PKGCONFIG := $(shell pkg-config --exists libconfig++ && echo yes || echo no)

ifeq ($(RAYLIB_PKGCONFIG),yes)
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib)
RAYLIB_LDFLAGS := $(shell pkg-config --libs raylib)
else
# Try Homebrew prefix as a fallback
HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null)
ifeq ($(HOMEBREW_PREFIX),)
RAYLIB_CFLAGS := -I/usr/local/include -I/opt/homebrew/include
RAYLIB_LDFLAGS := -L/usr/local/lib -L/opt/homebrew/lib -lraylib \
				  -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL \
				  -framework CoreFoundation -framework CoreGraphics -framework Foundation -framework AppKit \
				  -lobjc
else
RAYLIB_CFLAGS := -I$(HOMEBREW_PREFIX)/include -I/usr/local/include -I/opt/homebrew/include
RAYLIB_LDFLAGS := -L$(HOMEBREW_PREFIX)/lib -L/usr/local/lib -L/opt/homebrew/lib -lraylib \
				  -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL \
				  -framework CoreFoundation -framework CoreGraphics -framework Foundation -framework AppKit \
				  -lobjc
endif
endif

ifeq ($(LIBCONFIG_PKGCONFIG),yes)
LIBCONFIG_CFLAGS := $(shell pkg-config --cflags libconfig++)
LIBCONFIG_LDFLAGS := $(shell pkg-config --libs libconfig++)
else
# Fallback to plain linker flag; add Homebrew lib dir if available
LIBCONFIG_CFLAGS := -I/usr/local/include -I/opt/homebrew/include
LIBCONFIG_LDFLAGS := -L/usr/local/lib -L/opt/homebrew/lib -lconfig++
endif

# Add rpath so the executable can find Homebrew-installed dylibs at runtime
RPATH_FLAGS = -Wl,-rpath,/usr/local/lib -Wl,-rpath,/opt/homebrew/lib

# Generic search paths to help the linker find Homebrew libs regardless of prefix mismatches
GENERIC_LIB_PATHS = -L/usr/local/lib -L/opt/homebrew/lib

# On macOS, ensure required frameworks are always linked (some raylib.pc are incomplete)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
RAYLIB_LDFLAGS += -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL \
				  -framework CoreFoundation -framework CoreGraphics -framework Foundation -framework AppKit \
				  -lobjc
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
               -I$(SRC_DIR)/Builders \
		   -I$(SRC_DIR)/Factories \
		   $(RAYLIB_CFLAGS) \
		   $(LIBCONFIG_CFLAGS)


SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
# Exclude legacy SFML renderer if still present in tree
SRCS := $(filter-out $(SRC_DIR)/Renders/SFMLRenderer.cpp,$(SRCS))
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
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GENERIC_LIB_PATHS) $(RAYLIB_LDFLAGS) $(LIBCONFIG_LDFLAGS) $(RPATH_FLAGS)
	@echo "$(GREEN) $(NAME) successfully compiled! $(RESET)"

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

.PHONY: print-flags
print-flags:
	@echo "SFML_PKGCONFIG=$(SFML_PKGCONFIG)"
	@echo "LIBCONFIG_PKGCONFIG=$(LIBCONFIG_PKGCONFIG)"
	@echo "HOMEBREW_PREFIX=$(HOMEBREW_PREFIX)"
	@echo "RAYLIB_CFLAGS=$(RAYLIB_CFLAGS)"
	@echo "RAYLIB_LDFLAGS=$(RAYLIB_LDFLAGS)"
	@echo "LIBCONFIG_CFLAGS=$(LIBCONFIG_CFLAGS)"
	@echo "LIBCONFIG_LDFLAGS=$(LIBCONFIG_LDFLAGS)"
	@echo "RPATH_FLAGS=$(RPATH_FLAGS)"