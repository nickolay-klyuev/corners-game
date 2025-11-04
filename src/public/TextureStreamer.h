#pragma once

#include <unordered_map>

#include "SFML/Graphics.hpp"

enum class TextureType {
        BlackSlot,
        WhiteSlot,
        BlackPawn,
        WhitePawn
};

class TextureStreamer
{
        std::unordered_map<TextureType, sf::Texture> _loadedTextures;

public:
        TextureStreamer();
        ~TextureStreamer() = default;

        auto operator[](TextureType tt) const -> const sf::Texture& {
                return _loadedTextures.at(tt);
        }
};