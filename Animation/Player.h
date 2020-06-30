//
// Created by solov on 6/29/2020.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;
using namespace std;
#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H


class Player {
public:
    Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(RenderWindow& window);

private:
    RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
};


#endif //ANIMATION_PLAYER_H
