#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation {
public:
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    ~Animation();

    IntRect uvRect;

    void Update(int row, float deltaTime);

private:
    Vector2u imageCount;
    Vector2u currentImage;

    float totalTime;
    float switchTime;

};

int main(int argc, char** argv) {
    
    int width, height;
    width = VideoMode::getDesktopMode().width;
    height = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(width, height), "BETA", Style::Default);

    RectangleShape player(Vector2f(100, 100));
    player.setPosition(200, 200);

    Texture playerTexture;
    if (!playerTexture.loadFromFile("Resources/Player/States/Attack 1.png"))
        std::cout << "Texture::ERROR";

    player.setTexture(&playerTexture);
    player.setScale(5, 5);

    Animation animation(&playerTexture, Vector2u(5, 1), 0.2f);

    float deltaTime = 0;
    Clock clock;

    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();

        Event event;

        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                window.close();
        }

        animation.Update(0, deltaTime);
        player.setTextureRect(animation.uvRect);
        std::cout << animation.uvRect.width << '\n' << animation.uvRect.height;

        window.clear();
        window.draw(player);
        window.display();
    }
    return EXIT_SUCCESS;
}

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) {

    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime) {

    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {

        totalTime -= switchTime;
        currentImage.x++;
    }
    
    if (currentImage.x >= imageCount.x) {
        currentImage.x = 0;
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
