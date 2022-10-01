[ -f 2048game ] && rm 2048game
g++ -c list.c
g++ -c 2048game.c
g++ list.o 2048game.o -o 2048game
rm *.o
./2048game
