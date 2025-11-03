#pragma once

#include <unordered_map>
#include <array>
#include <string>

#include "SFML/Graphics.hpp"

class TextureStreamer
{
public:
        enum class TextureType {
                BlackSlot,
                WhiteSlot,
                BlackPawn,
                WhitePawn
        };

private:
        std::unordered_map<TextureType, sf::Texture> _loadedTextures;

public:
        TextureStreamer();
        ~TextureStreamer() = default;

        auto Get(TextureType tt) const -> const sf::Texture& {
                return _loadedTextures.at(tt);
        }

        auto GetSlotTexture() const -> const sf::Texture& {

        }
};