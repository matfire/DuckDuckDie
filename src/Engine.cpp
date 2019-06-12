#include "Engine.hpp"
#include "assetManager.hpp"
#include <random>
Engine::Engine() : _window({1280, 720}, "simple window"), _level(0), _score(0) {
    _window.setFramerateLimit(60);
}

Engine::~Engine(){}


void Engine::init(uint width, uint height, std::string name) {
    _window.setSize({width, height});
    _window.setTitle(name);
    assetManager::get().loadTexture("bg", "./assets/bg.png");
    assetManager::get().loadTexture("normal ducks", "./assets/ducks.png");
    assetManager::get().loadTexture("hard ducks", "./assets/ducks_hard.png");
    assetManager::get().loadFont("font", "./assets/emulogic.ttf");
}

void Engine::run() {

    //load background image
    sf::Sprite bg(*assetManager::get().getTexture("bg"));
    
    //setting up score text
    sf::Text score;
    score.setFont(*assetManager::get().getFont("font"));
    score.setCharacterSize(20);
    score.setString(std::to_string(_score));
    //instantiate factory
    DuckFactory factory;

    //create 2 ducks
    BaseDuck *hard = factory.createDuck("hard");
    BaseDuck *normal = factory.createDuck("normal");

    //random range generator
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(20, 200);

    //set initial position
    hard->getSprite()->setPosition({-110, distr(generator)});
    normal->getSprite()->setPosition({-110, distr(generator)});

    while(_window.isOpen()) {
        int lastScore = _score;
        //get deltaTime
        sf::Time elapsedTime = _timer.restart();

        //event handling
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mouseWorlCoord = sf::Mouse::getPosition(_window);
                if (hard->getSprite()->getGlobalBounds().contains(mouseWorlCoord.x, mouseWorlCoord.y)) {
                    if (hard->isDead()) {
                            hard->getSprite()->setPosition({-110, distr(generator)});
                            _score += 100;
                    }
                }
                if (normal->getSprite()->getGlobalBounds().contains(mouseWorlCoord.x, mouseWorlCoord.y)) {
                    normal->getSprite()->setPosition({-110, distr(generator)});
                    _score += 25;
                }
            }
        }
        if (_score % 50 == 0 && _score != lastScore) {
            _level += 1;
        }
        //check if either sprite is out of screen
        if (normal->getSprite()->getPosition().x > _window.getSize().x) {
            normal->getSprite()->setPosition({-110, distr(generator)});
        }
        if (hard->getSprite()->getPosition().x > _window.getSize().x) {
            hard->getSprite()->setPosition({-110, distr(generator)});
        }
        // hard sprite gets handled only after two levels
        if (_level > 2) {
            hard->move(hard->getSpeed() * 12 * (_level / 2) * elapsedTime.asSeconds(), 0);
            hard->update(elapsedTime);
        }
        normal->move(normal->getSpeed() * 10 * elapsedTime.asSeconds(), 0);
        normal->update(elapsedTime);

        //updates score text
        score.setString(std::to_string(_score));
        //clears window
        _window.clear();
        //draws background
        _window.draw(bg);
        //draws sprites
        _window.draw(*hard->getSprite());
        _window.draw(*normal->getSprite());
        //draws text
        _window.draw(score);
        // actually displays the window
        _window.display();
    }
}