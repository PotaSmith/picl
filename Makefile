CC = cc

FILES = src/*.c src/parser/*.c src/ast/*.c\
	

BISON_OUTPUT = src/parser/picl-parser.c src/parser/picl-parser.h

INCLUDE_DIR = src/include

FLAGS = -Wall -g -O2 -o bin/picl -I$(INCLUDE_DIR)

picl: $(FILES) $(BISON_OUTPUT)
	$(CC) $(FLAGS) $(FILES)

$(BISON_OUTPUT): src/parser/picl-parser.y
	bison -d -ra -o src/parser/picl-parser.c src/parser/picl-parser.y

parser:
	bison -d -ra -o src/parser/picl-parser.c src/parser/picl-parser.y

clean:
	rm $(BISON_OUTPUT) bin/picl








