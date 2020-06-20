// image from kindpng license for personal use only
// learned how to do this from https://www.youtube.com/watch?v=Aa8bXSq5LDE&t=3s (Creative Common Attribution license)
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(512,512),"Animation",Style::Close | Style::Resize);
    RectangleShape player(Vector2f(400.0f,400.0f));
    player.setPosition(156.0f,56.0f);
    Texture playerTexture;
    playerTexture.loadFromFile("images/player.png");
    player.setTexture(&playerTexture);
    Animation animation(&playerTexture,Vector2u(6,4),0.3f);
    float deltaTime = 0.0f;
    Clock clock;


    while(window.isOpen()){
        deltaTime = clock.restart().asSeconds();
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed){
                window.close();
            }
        }
        animation.Update(2,deltaTime);
        player.setTextureRect(animation.uvRect);

        window.clear();
        window.draw(player);
        window.display();
    }
    return 0;
}
