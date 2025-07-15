TARGET = duckmarketplace
TARGET_TUI = duckmarketplace_tui
SOURCES = main.c DuckMarketPlace_i.c
SOURCES_TUI = tui.c DuckMarketPlace_i.c

all: $(TARGET) $(TARGET_TUI)

run: $(TARGET)
	./$(TARGET)

run-tui: $(TARGET_TUI)
	./$(TARGET_TUI)

$(TARGET): $(SOURCES)
	gcc $(SOURCES) -o $(TARGET)

$(TARGET_TUI): $(SOURCES_TUI)
	gcc $(SOURCES_TUI) -o $(TARGET_TUI)

clean:
	rm -f $(TARGET) $(TARGET_TUI)
