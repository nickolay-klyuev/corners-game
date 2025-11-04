#pragma once

#include <functional>

#include "Input.h"
#include "GameField.h"

class AIEnemy {
        GameField* _gameField_ptr = nullptr;

        bool _isMakingMove = false;

public:
        AIEnemy() = delete;
        AIEnemy(GameField* gameField): _gameField_ptr(gameField) {}
        ~AIEnemy() = default;

        void StartMove();
        void Move();

        std::function<void()> AIMoveFinishedFunc;

private:
        int getRandomInt(int min, int max) const;
};