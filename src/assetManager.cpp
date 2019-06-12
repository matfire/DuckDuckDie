//
// Created by matteo on 16/04/19.
//

#include "assetManager.hpp"


void assetManager::loadTexture(std::string name, std::string path) {
    if (_textures.find(name) != _textures.end())
        throw std::runtime_error("texture " + name + " already exists");
    sf::Texture newTexture;
    if (!newTexture.loadFromFile(path)) {
        throw std::runtime_error("could not load texture " + name + " from path " + path);
    }
    _textures.emplace(name, new sf::Texture(newTexture));
    std::cout << "[+]AssetManager: loaded texture " << name << " from " << path << std::endl;
}

void assetManager::loadFont(std::string name, std::string path) {
    if (_fonts.find(name) != _fonts.end())
        throw std::runtime_error("font " + name + " already exists");
    sf::Font newFont;

    if (!newFont.loadFromFile(path))
        throw std::runtime_error("could not load font " + name + " from path " + path);
    std::cout << "[+]AssetManager: loaded font " << name << " from path " << path << std::endl;
    _fonts.emplace(name, new sf::Font(newFont));
}

sf::Font *assetManager::getFont(std::string name) {
    std::cout << "[+]AssetManager:: requested font " << name << std::endl;
    if (_fonts.find(name) == _fonts.end())
        throw std::runtime_error("could not find the font " + name + " in the loaded fonts");
    std::cout << "[+]AssetManager: requested font " << name << std::endl;
    return (_fonts.at(name));
}

sf::Texture *assetManager::getTexture(std::string name) {
    try {
        _textures.at(name);
    } catch (...) {
        throw std::runtime_error("texture with name " + name + " could not be found in loaded textures array" );
    }
    std::cout << "[+]AssetManager: requested texture " << name << std::endl;
    return _textures.at(name);
}