#!/usr/bin/env	bash

g++ -c src/Graphics.cpp -o graphics.o

g++ -c src/network.cpp -o network.o

g++ -c src/gui.cpp -o gui.o

g++ -c src/MovementComponent.cpp -o movementcomponent.o

g++ -c src/Entity.cpp -o entity.o

g++ -c src/Player.cpp -o player.o

g++ -c src/State.cpp -o state.o

g++ -c src/GameState.cpp -o gamestate.o

g++ -c src/MainMenuState.cpp -o mainmenustate.o

g++ -c src/OnlineMenuState.cpp -o onlinemenustate.o

g++ -c src/Game.cpp -o game.o

g++ -c src/main.cpp -o main.o

g++ -g -Wall -lm -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network graphics.o network.o gui.o movementcomponent.o entity.o player.o state.o gamestate.o mainmenustate.o onlinemenustate.o game.o main.o -o run

# Clear
rm *.o
