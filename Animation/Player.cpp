//
// Created by solov on 6/29/2020.
//
#include <iostream>
#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
    animation(texture,imageCount,switchTime)
{
    this->speed = speed;
    row = 0;
    faceRight = true;

    body.setSize(Vector2f(400.0f,400.0f));
    body.setPosition(56.0f,56.0f);
    body.setTexture(texture);
}
Player::~Player() {

}
void Player::Update(float deltaTime){
    Vector2f movement(0.0f,0.0f);
    if(Keyboard::isKeyPressed(Keyboard::A)){
        movement.x -= speed * deltaTime;
    }
    if(Keyboard::isKeyPressed(Keyboard::D)){
        movement.x += speed * deltaTime;
    }
    if(movement.x == 0.0f){
        row = 0;
    } else{
        row = 1;
        if(movement.x > 0.0f){
            faceRight = true;
        } else{
            faceRight = false;
        }
    }
    animation.Update(row,deltaTime,faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);

}
void Player :: Draw(RenderWindow& window) {
    window.draw(body);
}