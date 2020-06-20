// image from kindpng license for personal use only
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;




int main() {
    RenderWindow window(VideoMode(512,512),"Animation",Style::Close | Style::Resize);
    RectangleShape player(Vector2f(400.0f,400.0f));
    player.setPosition(56.0f,56.0f);
    Texture playerTexture;
    playerTexture.loadFromFile("images/player.png");
    player.setTexture(&playerTexture);
    Vector2u texturesize = playerTexture.getSize();
    texturesize.x /= 6;
    texturesize.y /= 4;
    player.setTextureRect(IntRect(texturesize.x*2, texturesize.y*2, texturesize.x,texturesize.y));

    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
