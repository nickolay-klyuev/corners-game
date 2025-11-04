#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "GameField.h"

class Input {
        GameField* _gameField_ptr = nullptr;
        const Renderer* _renderer_ptr = nullptr;

public:
        Input() = delete;
        Input(const Renderer* renderer, GameField* gameField)
                : _renderer_ptr(renderer), _gameField_ptr(gameField) {}
        ~Input() = default;

        void OnMouseLeftClicked(sf::Vector2f);
        void OnAIMoveFinished();

        std::function<void()> PlayerInputFinishedFunc;

        bool IsWaitingForEnemyMove = false;
};