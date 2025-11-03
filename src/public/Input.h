#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "GameField.h"

class Input {
        std::vector<sf::Sprite> _clickableSlots;
        std::vector<sf::Sprite> _clickablePawns;

        GameField<>* _gameField_ptr = nullptr;
        const Renderer* _renderer_ptr = nullptr;

public:
        Input() = delete;
        Input(const Renderer* renderer, GameField<>* gameField): _renderer_ptr(renderer), _gameField_ptr(gameField) {}
        ~Input() = default;

        void OnMouseLeftClicked(sf::Vector2f mouse) {
                for (const auto& slot : _renderer_ptr->GetRenderingSlotSprites()) {
                        if (slot.getGlobalBounds().contains(mouse)) {
                                std::cout << "CLICKED SLOT" << '\n';
                        }
                }
                
                for (const auto& [index, sprite] : _renderer_ptr->GetRenderingPawnMap()) {
                        if (sprite.getGlobalBounds().contains(mouse)) {
                                _gameField_ptr->Select(index);
                        }
                }
        }
};