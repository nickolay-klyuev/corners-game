#include "TextureStreamer.h"

#include <iostream>

TextureStreamer::TextureStreamer() {
        sf::Texture new_texture;
        if (!new_texture.loadFromFile("assets/dark-slot.png")) {
                std::cerr << "Could not load texture file!" << '\n';
        }

        _loadedTextures[TextureType::BlackSlot] = new_texture;

        if (!new_texture.loadFromFile("assets/white-slot.png")) {
                std::cerr << "Could not load texture file!" << '\n';
        }

        _loadedTextures[TextureType::WhiteSlot] = new_texture;

        if (!new_texture.loadFromFile("assets/black-pawn.png")) {
                std::cerr << "Could not load texture file!" << '\n';
        }

        _loadedTextures[TextureType::BlackPawn] = new_texture;

        if (!new_texture.loadFromFile("assets/white-pawn.png")) {
                std::cerr << "Could not load texture file!" << '\n';
        }

        _loadedTextures[TextureType::WhitePawn] = new_texture;
}