PROJECT_NAME = ui-file-resource
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -std=gnu11 
GTK_LIBS = `pkg-config --cflags --libs gtk4`
RESOURCE_FILES = resources.c

all: resources $(PROJECT_NAME)

resources: resources.xml
	glib-compile-resources resources.xml --generate-source --target=resources.c
	glib-compile-resources resources.xml --generate-header --target=resources.h

$(PROJECT_NAME): main.c $(RESOURCE_FILES)
	$(CC) $(CFLAGS) -o $(PROJECT_NAME) main.c resources.c $(GTK_LIBS)

clean:
	rm -f $(PROJECT_NAME) resources.c resources.h