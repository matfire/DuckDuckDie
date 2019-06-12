#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <list>
#include "ducks.hpp"

class Engine {
    public:
        Engine();
        ~Engine();
        void init(uint width, uint height, std::string title);
        void run();
        void update(sf::Time elapsedTime);
    private:
        sf::RenderWindow _window;
        sf::Clock _timer;
        sf::Event _event;
        int _level;
        int _score;
};