TARGET = ./main.out
TARGET2 = ./main_module.out
HDRS_DIR = project/include

SRCS = project/src/main.c \
       project/src/information.c \
       project/src/record.c \
       project/src/streams.c

SRCS2 = project/src/main_module.c \
	project/src/test_assistants.c

.PHONY: all build rebuild check test memtest clean

all: clean check test memtest

$(TARGET): $(SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TARGET2): $(SRCS2) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET2) $(CFLAGS) $(SRCS2)

build: $(TARGET)

build: $(TARGET2)

rebuild: clean build

check:
	./linters/run.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) $(TARGET2)
