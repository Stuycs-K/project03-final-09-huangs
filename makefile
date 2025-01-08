game.o: game.c
	@gcc -c game.c
compile game: game.o
	@gcc -o game game.o
run: game
	@./game
clean:
	@rm -f *.o
	@rm -f game
