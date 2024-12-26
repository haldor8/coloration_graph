CC = gcc
CFLAGS = -Wall -Wextra -std=c11 

# Liste des fichiers source, changer le nom des .c pour les compiler séparément
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

EXEC = color_graph

# Ne fonctionne que pour l'OS lui-même, si on utilise Cygwin sur Windows, il faut utiliser "man_clean_l"
ifeq ($(OS),Windows_NT)
    RM = del /Q
else
    RM = rm -f
endif

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	$(RM) *.o
	$(RM) *.exe

# Règle pour nettoyer manuellement
man_clean_w:
	del *.o
	del *.exe

man_clean_l:
	RM -f *.o
	RM -f *.exe