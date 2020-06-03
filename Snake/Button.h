//
// Created by solov on 6/1/2020.
// Credits to https://www.youtube.com/watch?v=T31MoLJws4U by TermSpar

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#ifndef SNAKE_BUTTON_H
#define SNAKE_BUTTON_H

class Button {
public:
    Button(){}
    Button(string t,Vector2f size, int charsize, Color bgColor, Color txtcolor){
    text.setString(t);
    text.setFillColor(txtcolor);
    text.setCharacterSize(charsize);

    button.setSize(size);
    button.setFillColor(bgColor);
    }
    void setFont(Font &font){
        text.setFont(font);
    }
    void setBackColor(Color color){
        button.setFillColor(color);
    }
    void setTextColor(Color color){
        text.setFillColor(color);
    }
    void setPosition(Vector2f pos){
        button.setPosition(pos);

        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos,yPos);
    }
    void drawTo(RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }
    bool isMouseOver(RenderWindow &window){
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnXPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnYPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY){
            return true;
        }
        return false;
    }

private:
    RectangleShape button;
    Text text;
};

#endif //SNAKE_BUTTON_H
