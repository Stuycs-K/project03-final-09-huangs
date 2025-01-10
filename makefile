game.o: game.c
	@gcc -c game.c
host.o: host.c
	@gcc -c host.c
player.o: player.c
	@gcc -c player.c
compile: game.o host.o player.o
	@gcc -o host host.o game.o
	@gcc -o player player.o
run: game
	@./game
clean:
	@rm -f *.o
	@rm -f game
