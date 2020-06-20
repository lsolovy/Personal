//
// Created by solov on 6/20/2020.
//
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#ifndef ANIMATION_ANIMATION_H
#define ANIMATION_ANIMATION_H


class Animation {
public:
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();

    IntRect uvRect;

private:
    Vector2u imageCount;
    Vector2u currentImage;

    float totalTime;
    float switchTime;

};


#endif //ANIMATION_ANIMATION_H
