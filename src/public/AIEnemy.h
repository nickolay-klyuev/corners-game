#pragma once

#include "Input.h"
#include "GameField.h"

class AIEnemy {
        Input* _input_ptr = nullptr;
        GameField* _gameField_ptr = nullptr;

        bool _moveStarted = false;

public:
        AIEnemy() = delete;
        AIEnemy(Input* input, GameField* gameField)
                : _input_ptr(input), _gameField_ptr(gameField) {}
        ~AIEnemy() = default;

        void Update();
        void MakeMove();

private:
        int getRandomInt(int min, int max) const;
};