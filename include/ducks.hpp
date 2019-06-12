#pragma once

#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "assetManager.hpp"

class BaseDuck {
    public:
        BaseDuck(std::string name, sf::Time time) : _sprite(time, false, true) {
            _animation.setSpriteSheet(*assetManager::get().getTexture(name));
            _animation.addFrame(sf::IntRect(0, 0, 110, 110));
			_animation.addFrame(sf::IntRect(110, 0, 110, 110));
			_animation.addFrame(sf::IntRect(220, 0, 110, 110));
            _sprite.setAnimation(_animation);
        }
        ~BaseDuck(){};
        float getSpeed() {return _speed;};
        AnimatedSprite *getSprite(){return &_sprite;};
        Animation *getAnimation(){return &_animation;};
        void update(sf::Time elapsedTime) {_sprite.update(elapsedTime);};
        void move(float x, float y) {_sprite.move(x, y);};
        virtual bool isDead() = 0;
    protected:
        AnimatedSprite _sprite;
        Animation _animation;
        float _speed;
};


class EasyDuck : public BaseDuck {
    public:
    EasyDuck(): BaseDuck("normal ducks", sf::seconds(0.2)) {
        _speed = 5;
    }
    bool isDead(){return true;};
    ~EasyDuck(){};
};

class HardDuck: public BaseDuck {
    public:
    HardDuck(): BaseDuck("hard ducks", sf::seconds(0.1)) {
        _speed = 10;
        _lives = 5;
    }
    bool isDead() {
        _lives = _lives > 0 ? _lives - 1 : 0;
        if (_lives == 0) {
            _lives = 5;
            return true;
        }
        return false;
    }
    private:
        int _lives;
};

class DuckFactory {
    public:
    DuckFactory(){};
    ~DuckFactory(){};
    BaseDuck *createDuck(std::string name) {
        if (name == "normal")
            return new EasyDuck();
        if (name == "hard")
            return new HardDuck();
        throw std::runtime_error("No duck named " + name + " was defined in this DuckFactory");
    }
};