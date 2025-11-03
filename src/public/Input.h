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
        bool IsWaitingForEnemyMove = false;

public:
        Input() = delete;
        Input(const Renderer* renderer, GameField<>* gameField): _renderer_ptr(renderer), _gameField_ptr(gameField) {}
        ~Input() = default;

        void OnMouseLeftClicked(sf::Vector2f mouse) {
                if (IsWaitingForEnemyMove) {
                        return;
                }

                for (const auto& [index, sprite] : _renderer_ptr->GetRenderingPawnMap()) {
                        if ((*_gameField_ptr)[index] == 1) {
                                continue;
                        }
                        
                        if (sprite.getGlobalBounds().contains(mouse)) {
                                _gameField_ptr->Select(index);
                        }
                }

                for (const auto& [index, slot_sprite] : _renderer_ptr->GetRenderingSlotMap()) {
                        if (slot_sprite.getGlobalBounds().contains(mouse)) {
                                IsWaitingForEnemyMove = _gameField_ptr->MoveIfPossible(index);
                        }
                }
        }
};