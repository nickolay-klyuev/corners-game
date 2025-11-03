#pragma once

#include <vector>
#include <unordered_map>
#include <map>

#include "SFML/Graphics.hpp"
#include "GameField.h"
#include "TextureStreamer.h"

class Renderer {
        // Not smart pointers because Renderer is not an owner of these classes. 
        // I use raw pointers when one uses something and smart pointers when one is an owner of something.
        GameField<>* _gameField_ptr = nullptr;
        sf::RenderWindow* _window_ptr = nullptr;
        TextureStreamer _textureStreamer;

        std::vector<sf::Sprite> _renderingSlotSprites;
        std::vector<sf::Sprite> _renderingPawnSprites;

        std::map<std::pair<int, int>, sf::Sprite> _renderingSlotMap;
        std::map<std::pair<int, int>, sf::Sprite> _renderingPawnMap;

public:
        Renderer() = delete;
        Renderer(GameField<>* gameField_ptr, sf::RenderWindow* window_ptr);
        ~Renderer() = default;

        void Render();

private:
        bool _flipFlopFlag = false;
        inline void ChangeFlipFlopFlag() {
                _flipFlopFlag = !_flipFlopFlag;
        }
        auto GetSlotTexture_FlipFlop() -> const sf::Texture&;

public:
        auto GetRenderingSlotSprites() const -> const std::vector<sf::Sprite>& {
                return _renderingSlotSprites;
        }

        auto GetRenderingPawnSprites() const -> const std::vector<sf::Sprite>& {
                return _renderingPawnSprites;
        }

        auto GetRenderingPawnMap() const -> const std::map<std::pair<int, int>, sf::Sprite>& {
                return _renderingPawnMap;
        }
};