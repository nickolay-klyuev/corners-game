#pragma once

#include <map>

#include "SFML/Graphics.hpp"

#include "GameField.h"
#include "TextureStreamer.h"

class Renderer {
public:
        static constexpr float SlotSize = 50.f;
        static constexpr float SlotPaddingSize = 5.f;
        static constexpr float SlotSizeWithPadding = SlotSize + SlotPaddingSize;

private:
        GameField* _gameField_ptr = nullptr;
        sf::RenderWindow* _window_ptr = nullptr;
        
        TextureStreamer _textureStreamer;

        std::map<std::pair<int, int>, sf::Sprite> _renderingSlotMap;
        std::map<std::pair<int, int>, sf::Sprite> _renderingPawnMap;

public:
        Renderer() = delete;
        Renderer(GameField* gameField_ptr, sf::RenderWindow* window_ptr);
        ~Renderer() = default;

        void Render();

        auto GetRenderingPawnMap() const -> const std::map<std::pair<int, int>, sf::Sprite>& {
                return _renderingPawnMap;
        }

        auto GetRenderingSlotMap() const -> const std::map<std::pair<int, int>, sf::Sprite>& {
                return _renderingSlotMap;
        }

private:
        bool _flipFlopFlag = false;
        void reverseFlipFlopFlag() {
                _flipFlopFlag = !_flipFlopFlag;
        }
        auto getSlotTexture_FlipFlop() -> const sf::Texture&;
};