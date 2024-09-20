//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Joseph Mi, Sept 15

#include "Ball.h" 
#include "Globals.h"
#include "Player.h" 
#include <cmath>

// Constructor
Ball::Ball() : velocity_x(5), velocity_y(5), x(WIDTH/2), y(HEIGHT/2), width(1), height(1), id(0) {}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id)
    : velocity_x(velocity_x), velocity_y(velocity_y), x(x), y(y), width(1), height(1), id(id) {}

void Ball::update() {
    velocity_y -= 0.02 * timeStep; // Apply gravity to velocity

    x += velocity_x * timeStep;
    y += velocity_y * timeStep;
}

void Ball::draw(Screen& screen) {
    screen.addPixel(x, y, 'o');
}

void Ball::bounce(Ball arr[], int ballCount, Player player) {
    // bouncwe off top and bottom walls
    if (y < 0) {
        y = -y;
        velocity_y = -velocity_y;
    } else if (y >= HEIGHT) {
        y = HEIGHT - 2;
        velocity_y = -velocity_y;
    }

    // Bouncing off left and right walls
    if (x < 0) {
        x = 0;
        velocity_x = -velocity_x;
    } else if (x >= WIDTH) {
        x = WIDTH - 2;
        velocity_x = -velocity_x;
    }

    // Bouncing off player
    if (overlap(player) != NO_OVERLAP) {
        velocity_x = -velocity_x;
    }

    // Bouncing off other balls
    for (int ball = 0; ball < ballCount; ball++) {
        if (arr[ball].getID() != id) { // Can't bounce off itself
            int overlapType = overlap(arr[ball]);

            if (overlapType == HORIZONTAL_OVERLAP) {
                velocity_x = -velocity_x;
            } else if (overlapType == VERTICAL_OVERLAP) {
                velocity_y = -velocity_y;
            }
        }
    }
}

int Ball::getID() {
    return id;
}

double Ball::getX() {
    return x;
}

int Ball::overlap(Ball& b) {
    // Check for horizontal overlap and then vertical overlap
    bool horizontalOverlap = (std::abs(x - b.x) < width);
    bool verticalOverlap = (std::abs(y - b.y) < height);

    if (horizontalOverlap && verticalOverlap) {
        if (std::abs(x - b.x) < std::abs(y - b.y)) {
            return HORIZONTAL_OVERLAP;
        } else {
            return VERTICAL_OVERLAP;
        }
    }

    return NO_OVERLAP;
}

int Ball::overlap(Player& p) {
    double p_x = p.getX();
    double p_y = p.getY();

    double p_width = p.getWidth();
    double p_height = p.getHeight();

    bool horizontalOverlap = (x < p_x + p_width && x + width > p_x);
    bool verticalOverlap = (y < p_y + p_height && y + height > p_y);

    // Determine type of overlap
    if (horizontalOverlap && verticalOverlap) {
        if (std::abs(x - p_x) > std::abs(y - p_y)) {
            return HORIZONTAL_OVERLAP;
        } else {
            return VERTICAL_OVERLAP;
        }
    }

    return NO_OVERLAP;
}