# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 00:00:00 by jcrochet          #+#    #+#              #
#    Updated: 2025/11/29 23:43:15 by jcrochet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Noms des programmes
CLIENT = client
SERVER = server

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
WAIT ?= 700

# Ajouter la définition de WAIT aux flags
CFLAGS += -DWAIT=$(WAIT)

# Dossiers
SRC_DIR = sources
PRINTF_DIR = $(SRC_DIR)/printf

# Fichiers sources
CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c
UTILS_SRC = $(SRC_DIR)/utils.c

# Fichiers objets
CLIENT_OBJ = $(SRC_DIR)/client.o
SERVER_OBJ = $(SRC_DIR)/server.o
UTILS_OBJ = $(SRC_DIR)/utils.o
PRINTF_OBJ = $(PRINTF_DIR)/ft_printf.o $(PRINTF_DIR)/ft_utils.o $(PRINTF_DIR)/ft_utils_2.o

# Headers
HEADER = $(SRC_DIR)/talk.h
PRINTF_HEADER = $(PRINTF_DIR)/ft_printf.h

# Règle principale
all: $(CLIENT) $(SERVER)
	@echo "✓ Compiled with WAIT=$(WAIT) microseconds"

# Compilation du client
$(CLIENT): $(CLIENT_OBJ) $(UTILS_OBJ) $(PRINTF_OBJ)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(UTILS_OBJ) $(PRINTF_OBJ)
	@echo "✓ Client compiled"

# Compilation du serveur
$(SERVER): $(SERVER_OBJ) $(UTILS_OBJ) $(PRINTF_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) $(UTILS_OBJ) $(PRINTF_OBJ)
	@echo "✓ Server compiled"

# Compilation des fichiers objets
$(SRC_DIR)/client.o: $(CLIENT_SRC) $(HEADER) $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ)

$(SRC_DIR)/server.o: $(SERVER_SRC) $(HEADER) $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ)

$(SRC_DIR)/utils.o: $(UTILS_SRC) $(HEADER)
	$(CC) $(CFLAGS) -c $(UTILS_SRC) -o $(UTILS_OBJ)

$(PRINTF_DIR)/ft_printf.o: $(PRINTF_DIR)/ft_printf.c $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $(PRINTF_DIR)/ft_printf.c -o $(PRINTF_DIR)/ft_printf.o

$(PRINTF_DIR)/ft_utils.o: $(PRINTF_DIR)/ft_utils.c $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $(PRINTF_DIR)/ft_utils.c -o $(PRINTF_DIR)/ft_utils.o

$(PRINTF_DIR)/ft_utils_2.o: $(PRINTF_DIR)/ft_utils_2.c $(PRINTF_HEADER)
	$(CC) $(CFLAGS) -c $(PRINTF_DIR)/ft_utils_2.c -o $(PRINTF_DIR)/ft_utils_2.o

# Nettoyage
clean:
	rm -f $(SRC_DIR)/client.o $(SRC_DIR)/server.o $(SRC_DIR)/utils.o
	rm -f $(PRINTF_DIR)/ft_printf.o $(PRINTF_DIR)/ft_utils.o $(PRINTF_DIR)/ft_utils_2.o
	@echo "✓ Object files cleaned"

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	@echo "✓ Executables removed"

re: fclean all

# Tests rapides avec différentes valeurs de WAIT
test-fast: fclean
	@make WAIT=300
	@echo "=== Compiled with WAIT=300 ==="

test-normal: fclean
	@make WAIT=700
	@echo "=== Compiled with WAIT=700 ==="

test-slow: fclean
	@make WAIT=1500
	@echo "=== Compiled with WAIT=1500 ==="

# Help
help:
	@echo "Available targets:"
	@echo "  make              - Compile with default WAIT=700"
	@echo "  make WAIT=500     - Compile with custom WAIT value"
	@echo "  make test-fast    - Compile with WAIT=300"
	@echo "  make test-normal  - Compile with WAIT=700"
	@echo "  make test-slow    - Compile with WAIT=1500"
	@echo "  make clean        - Remove object files"
	@echo "  make fclean       - Remove object files and executables"
	@echo "  make re           - Recompile everything"

.PHONY: all clean fclean re test-fast test-normal test-slow help