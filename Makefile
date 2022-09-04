TARGET    := lostc

OBJ_DIR   := build
SRC_DIR   := src

SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.c") 
OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))
DEP_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.d,$(SRC_FILES))

SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
OBJ_SUBDIRS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC_SUBDIRS)) 

CFLAGS += -Wall -Wextra -pedantic -I src/ -std=c11 -Wno-missing-field-initializers -Wno-unused-parameter
LDFLAGS += -lGL -lglut -lGLU -lm

.PHONY: all clean segf

all: $(TARGET)
segf: CFLAGS += -Og -g -fsanitize=address
segf: LDFLAGS += -Og -g -fsanitize=address
segf: $(TARGET)

$(TARGET): $(OBJ_SUBDIRS) $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -MD $(CFLAGS) -c $< -o $@

#build/glad/glad.o: glad/src/glad.c
#	$(CC) -MMD -MP $(CFLAGS) -c $< -o $@

$(OBJ_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(TARGET) $(OBJ_SUBDIRS) 

-include $(DEP_FILES)
