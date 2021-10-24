TARGET = ./main.out
TARGET_TEST = ./test_module.out
HDRS_DIR = project/include

SRCS = project/src/main.c \
       project/src/information.c \
       project/src/record.c \
       project/src/streams.c

SRCS_TEST = project/src/test_module.c \
	project/src/test_assistants.c

.PHONY: all build rebuild check test memtest clean

all: clean check test memtest

$(TARGET): $(SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TARGET2): $(SRCS_TEST) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)

build: $(TARGET)

build: $(TARGET_TEST)

rebuild: clean build

check:
	./linters/run.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) $(TARGET_TEST)
