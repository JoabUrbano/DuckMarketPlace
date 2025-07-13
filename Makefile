TARGET = duckmarketplace
SOURCES = main.c DuckMarketPlace_i.c

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(SOURCES)
	gcc $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
