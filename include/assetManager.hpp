
#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class assetManager {
public:
    static assetManager& get()
    {
        static assetManager instance;
        return instance;
    }
    assetManager(assetManager const&) = delete;
    void operator=(assetManager const&) = delete;
    void loadTexture(std::string name, std::string path);
    void loadFont(std::string name, std::string path);
    sf::Texture *getTexture(std::string name);
    sf::Font *getFont(std::string name);
private:
    assetManager(){};
    ~assetManager(){
        _textures.clear();
        _fonts.clear();
    }
    std::map<std::string, sf::Texture*> _textures;
    std::map<std::string, sf::Font*> _fonts;
};