# Derleyici
CC = gcc

# GTK4 kütüphane ayarlarını otomatik al
CFLAGS = $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4)

# Hedef dosya adı
TARGET = hyprtheme

# Kaynak dosya
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)
