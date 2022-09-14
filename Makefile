TARGET    := lostc

OBJ_DIR   := build
SRC_DIR   := src
RES_DIR   := res
TEXTURE_DIR := $(RES_DIR)/textures

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.c") 
RES_FILES := $(shell find $(RES_DIR) -type f) 

OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)/$(SRC_DIR)%.o,$(SRC_FILES)) $(patsubst $(RES_DIR)%,$(OBJ_DIR)/$(RES_DIR)%.o,$(RES_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)/$(SRC_DIR)%.d,$(SRC_FILES))

OBJ_SUBDIRS := $(shell find $(SRC_DIR) $(RES_DIR) -type d | sed -E 's/^/$(OBJ_DIR)\//g')

CFLAGS += -Wall -Werror -Wextra -pedantic -std=c17 -Wno-missing-field-initializers -Wno-unused-parameter -O2
LDFLAGS += -lGL  -lpng -lGLU -lm -lglfw

.PHONY: all clean segf

all: $(TARGET)
segf: CFLAGS += -Og -g -fsanitize=address
segf: LDFLAGS += -Og -g -fsanitize=address
segf: $(TARGET)

$(TARGET): $(OBJ_SUBDIRS) $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/$(TEXTURE_DIR)/%.o: $(TEXTURE_DIR)/%
	python3 tools/imgconvert.py $<
	$(CC) $(CFLAGS) -c a.c -o $@
	rm a.c

$(OBJ_DIR)/$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -MMD -MD $(CFLAGS) -c $< -o $@

#build/glad/glad.o: glad/src/glad.c
#	$(CC) -MMD $(CFLAGS) -c $< -o $@

$(OBJ_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(TARGET) $(OBJ_SUBDIRS) 

-include $(DEP_FILES)
