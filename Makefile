# Macros para compilacao
CC = gcc
CFLAGS_1 = -lfreeimage
CFLAGS_2 = -lpthread
DIR = src
FILE_1 = $(DIR)/main.c
FILE_2 = $(DIR)/main_process.c
FILE_3 = $(DIR)/main_thread.c
IMGP = $(DIR)/imageprocessing.o
TARGET_1 = ./main
TARGET_2 = ./main_process
TARGET_3 = ./main_thread

# Macros para teste
BASH = sh
TEST_SCRIPT = test.sh

#Compila os códigos e gera programas
all:$(TARGET_1) $(TARGET_2) $(TARGET_3)

$(TARGET_1):$(FILE_1) $(IMGP)
	$(CC) -o$(TARGET_1) $(FILE_1) $(IMGP) -I $(DIR) $(CFLAGS_1)
$(TARGET_2):$(FILE_2) $(IMGP)
	$(CC) -o$(TARGET_2) $(FILE_2) $(IMGP) -I $(DIR) $(CFLAGS_1)
$(TARGET_3):$(FILE_3) $(IMGP)
	$(CC) -o$(TARGET_3) $(FILE_3) $(IMGP) -I $(DIR) $(CFLAGS_1) $(CFLAGS_2)

#Executa os programas
test:all
	$(BASH) $(TEST_SCRIPT)