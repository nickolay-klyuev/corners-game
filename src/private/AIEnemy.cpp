#include "AIEnemy.h"

#include <random>
#include <thread>
#include <chrono>

void AIEnemy:: Update() {
        if (_moveStarted) {
                return;
        }

        if (_input_ptr->IsWaitingForEnemyMove) {
                
                _moveStarted = true;

                std::thread makeMoveDelay(&AIEnemy::MakeMove, this);
                makeMoveDelay.detach();
        }
}

void AIEnemy::MakeMove() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto indexes = _gameField_ptr->GetWhitesIndexes();
        
        auto select = indexes[getRandomInt(0, indexes.size() - 1)];

        _gameField_ptr->Select(select);
        _gameField_ptr->Log();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (getRandomInt(0, 1)) {
                if (_gameField_ptr->CanBeMovedBottom(select)) {
                        _gameField_ptr->MoveIfPossible({ select.first, select.second + 1 });
                } else if (_gameField_ptr->CanBeMovedRight(select)) {
                        _gameField_ptr->MoveIfPossible({ select.first + 1, select.second });
                }
        } else {
                if (_gameField_ptr->CanBeMovedRight(select)) {
                        _gameField_ptr->MoveIfPossible({ select.first + 1, select.second });
                } else if (_gameField_ptr->CanBeMovedBottom(select)) {
                        _gameField_ptr->MoveIfPossible({ select.first, select.second + 1 });
                }
        }

        _moveStarted = false;
        _input_ptr->IsWaitingForEnemyMove = false;
}

int AIEnemy::getRandomInt(int min, int max) const {
        static std::random_device rd;
        static std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dist(min, max);
        
        return dist(gen);
}