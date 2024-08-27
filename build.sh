#!/usr/bin/env	bash

g++ -c src/Graphics.cpp -o graphics.o

g++ -c src/network.cpp -o network.o

g++ -c src/gui.cpp -o gui.o

g++ -c src/Menu.cpp -o menu.o

g++ -c src/Tile.cpp -o tile.o

g++ -c src/Level.cpp -o level.o

gcc -c src/HitboxComponent.cpp -o hitboxcomponent.o

g++ -c src/MovementComponent.cpp -o movementcomponent.o

g++ -c src/AttributeComponent.cpp -o attributecomponent.o

g++ -c src/AnimationComponent.cpp -o animationcomponent.o

g++ -c src/AIComponent.cpp -o aicomponent.o

g++ -c src/AIFollow.cpp -o aifollow.o

g++ -c src/Entity.cpp -o entity.o

g++ -c src/Enemy.cpp -o enemy.o

g++ -c src/Player.cpp -o player.o

g++ -c src/State.cpp -o state.o

g++ -c src/GameState.cpp -o gamestate.o

g++ -c src/MainMenuState.cpp -o mainmenustate.o

g++ -c src/HeroCreateState.cpp -o herocreatestate.o

g++ -c src/Game.cpp -o game.o

g++ -c src/main.cpp -o main.o

g++ -g -Wall -lm -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network graphics.o network.o gui.o menu.o tile.o level.o hitboxcomponent.o movementcomponent.o attributecomponent.o animationcomponent.o aicomponent.o aifollow.o entity.o enemy.o player.o state.o gamestate.o mainmenustate.o herocreatestate.o game.o main.o -o run

# Clear
rm *.o
