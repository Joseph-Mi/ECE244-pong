//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Joseph Mi on Sept 15
//

#include "Ball.h"
#include "Globals.h"
#include "Player.h"  

Player::Player() : x(0), y(HEIGHT/2), height(10), width(1) {}

Player::Player(double x, double y, int h) : x(x), y(y), height(h), width(1) {}

double Player::getX() {
    return x;
}

double Player::getY() {
    return y;
}

int Player::getHeight() {
    return height;
}

int Player::getWidth() {
    return width;
}

void Player::decreaseHeight(int delta_to_decrease_by) {
    height = (height - delta_to_decrease_by >= 3) ? height - delta_to_decrease_by : 3;
}

void Player::update(char direction) {
    const int speed = 2;
    
    if (direction == 'A') { // Up
        y = (y + speed < HEIGHT - height) ? y + speed : HEIGHT - height;
        } else if (direction == 'B') { // Down
        y = (y - speed > 0) ? y - speed : 0;
    }
}

void Player::draw(Screen& screen) {
    for (int i = 0; i < height; i++) {
        screen.addPixel(x, y + i, '#');
    }
}