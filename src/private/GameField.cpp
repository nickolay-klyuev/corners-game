#include "GameField.h"

#include <iostream>

auto GameField::GetWhitesIndexes() const -> std::vector<std::pair<int, int>> {
        std::vector<std::pair<int, int>> indexes;

        for (int i = 0; i < _data.size(); ++i) {
                for (int j = 0; j < _data[i].size(); ++j) {
                        if (_data[i][j] == 1 && CanBeMovedRightBottom({ i, j })) {
                                indexes.emplace_back(i, j);
                        }
                }
        }

        return indexes;
}

void GameField::UnselectAll() {
        for (auto& data_column : _data) {
                for (auto& slot : data_column) {

                        switch (slot) {
                                case SlotType::MoveAllowed:
                                        slot = SlotType::Empty;
                                        break;
                                case SlotType::WhitePawnSelected:
                                        slot = SlotType::WhitePawn;
                                        break;
                                case SlotType::BlackPawnSelected:
                                        slot = SlotType::BlackPawn;
                                default:
                                        break;
                        }
                }
        }

        _selected = { -1, -1 };
}

void GameField::Select(std::pair<int, int> index) {
        UnselectAll();

        auto& slot = (*this)[index];

        if (slot == SlotType::BlackPawn || slot == SlotType::WhitePawn) {
                if (slot == SlotType::BlackPawn) {
                        slot = SlotType::BlackPawnSelected;
                } else if (slot == SlotType::WhitePawn) {
                        slot = SlotType::WhitePawnSelected;
                }

                IsDirtyFlag = true;

                _selected = index;

                if (index.first < Size - 1 && _data[index.first + 1][index.second] == 0) {
                        _data[index.first + 1][index.second] = SlotType::MoveAllowed;
                }

                if (index.first > 0 && _data[index.first - 1][index.second] == 0) {
                        _data[index.first - 1][index.second] = SlotType::MoveAllowed;
                }

                if (index.second < Size - 1 && _data[index.first][index.second + 1] == 0) {
                        _data[index.first][index.second + 1] = SlotType::MoveAllowed;
                }

                if (index.second > 0 && _data[index.first][index.second - 1] == 0) {
                        _data[index.first][index.second - 1] = SlotType::MoveAllowed;
                }
        }

}

bool GameField::CanBeMovedSomewhere(std::pair<int, int> index) const {
        return (index.first < 7 && _data[index.first + 1][index.second]) == 0 ||
                (index.first > 0 && _data[index.first - 1][index.second]) == 0 ||
                (index.second < 7 && _data[index.first][index.second + 1]) == 0 ||
                (index.second > 0 && _data[index.first][index.second - 1]) == 0;
}

bool GameField::CanBeMovedRightBottom(std::pair<int, int> index) const {
        return (index.first < 7 && _data[index.first + 1][index.second]) == 0 ||
                (index.second < 7 && _data[index.first][index.second + 1] == 0);
}

bool GameField::CanBeMovedRight(std::pair<int, int> index) const {
        return index.first < 7 && (_data[index.first + 1][index.second] == 3);
}

bool GameField::CanBeMovedBottom(std::pair<int, int> index) const {
        return index.second < 7 && (_data[index.first][index.second + 1] == 3);
}

bool GameField::MoveIfPossible(std::pair<int, int> index) {
        if (_data[index.first][index.second] == SlotType::MoveAllowed) {
                std::swap(_data[_selected.first][_selected.second], _data[index.first][index.second]);

                IsDirtyFlag = true;
                IsPawnsDirtyFlag = true;

                UnselectAll();

                return true;
        }

        return false;
}

void GameField::Log() const {
        for (auto cols : _data) {
                for (auto slot : cols) {
                        std::cout << slot << " ";
                }
                std::cout << '\n';
        }
}