//
// Created by solov on 6/20/2020.
//

#include "Animation.h"
Animation :: Animation(Texture* texture, Vector2u imageCount, float switchTime);{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}
Animation::~Animation() {

}