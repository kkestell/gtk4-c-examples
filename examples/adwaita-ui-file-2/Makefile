PROJECT_NAME = adwaita-ui-file-2
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -std=gnu11
GTK_LIBS = `pkg-config --cflags --libs gtk4 libadwaita-1`

all: $(PROJECT_NAME)

$(PROJECT_NAME): main.c
	$(CC) $(CFLAGS) -o $(PROJECT_NAME) main.c $(GTK_LIBS)

clean:
	rm -f $(PROJECT_NAME)
