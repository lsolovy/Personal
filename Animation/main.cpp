// image from kindpng license for personal use only
// learned how to do this from https://www.youtube.com/watch?v=Aa8bXSq5LDE&t=3s (Creative Common Attribution license)
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(512,512),"Animation",Style::Close | Style::Resize);


    Texture playerTexture;
    playerTexture.loadFromFile("images/player.png");

    Player player(&playerTexture,Vector2u(6,4),0.3f,100.0f);
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
        player.Update(deltaTime);

        window.clear();
        player.Draw(window);
        window.display();
    }
    return 0;
}
