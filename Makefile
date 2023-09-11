CC := clang
CFLAGS := -g 

all: server client

clean:
	rm -rf import server client

server: import.c socket.h message.c server.c message.h
	$(CC) $(CFLAGS) -o server import.c server.c message.c -lpthread

client: client.c message.h message.c import.c socket.h
	$(CC) $(CFLAGS) -o client client.c message.c import.c

zip:
	@echo "Generating finalproject.zip file to submit to Gradescope..."
	@zip -q -r finalproject.zip . -x .git/\* .vscode/\* .clang-format .gitignore import
	@echo "Done. Please upload finalproject.zip to Gradescope."

format:
	@echo "Reformatting source code."
	@clang-format -i --style=file $(wildcard *.c) $(wildcard *.h)
	@echo "Done."

.PHONY: all clean zip format
