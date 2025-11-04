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

                markSlotsForMove(Direction::Right, index);
                markSlotsForMove(Direction::Left, index);
                markSlotsForMove(Direction::Bottom, index);
                markSlotsForMove(Direction::Top, index);
        }

}

bool GameField::CanBeMovedRightBottom(std::pair<int, int> index) const {
        return (index.first < Size - 1 && _data[index.first + 1][index.second]) == SlotType::Empty ||
                (index.second < Size - 1 && _data[index.first][index.second + 1] == SlotType::Empty);
}

bool GameField::CanBeMovedRight(std::pair<int, int> index) const {
        return index.first < Size - 1 && (_data[index.first + 1][index.second] == SlotType::MoveAllowed);
}

bool GameField::CanBeMovedBottom(std::pair<int, int> index) const {
        return index.second < Size - 1 && (_data[index.first][index.second + 1] == SlotType::MoveAllowed);
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

void GameField::markSlotsForMove(Direction direction, std::pair<int, int> index, bool jump_check) {

        switch (direction) {
                case Direction::Right:

                        if (index.first < Size - 1) {
                                if (!jump_check && isEmptySlot(direction, index)) {
                                        _data[index.first + 1][index.second] = SlotType::MoveAllowed;
                                        return;
                                }
                                
                                if (!isEmptySlot(direction, index) && isEmptySlot(direction, { index.first + 1, index.second })) {
                                        _data[index.first + 2][index.second] = SlotType::MoveAllowed;
                                        markSlotsForMove(direction, { index.first + 2, index.second }, true);
                                }
                        }

                        break;

                case Direction::Left:

                        if (index.first > 0) {
                                if (!jump_check && isEmptySlot(direction, index)) {
                                        _data[index.first - 1][index.second] = SlotType::MoveAllowed;
                                        return;
                                }
                                
                                if (!isEmptySlot(direction, index) && isEmptySlot(direction, { index.first - 1, index.second })) {
                                        _data[index.first - 2][index.second] = SlotType::MoveAllowed;
                                        markSlotsForMove(direction, { index.first - 2, index.second }, true);
                                }
                        }

                        break;
                
                case Direction::Bottom:

                        if (index.second < Size - 1) {
                                if (!jump_check && isEmptySlot(direction, index)) {
                                        _data[index.first][index.second + 1] = SlotType::MoveAllowed;
                                        return;
                                }
                                
                                if (!isEmptySlot(direction, index) && isEmptySlot(direction, { index.first, index.second + 1 })) {
                                        _data[index.first][index.second + 2] = SlotType::MoveAllowed;
                                        markSlotsForMove(direction, { index.first, index.second + 2 }, true);
                                }
                        }

                        break;

                case Direction::Top:

                        if (index.second > 0) {
                                if (!jump_check && isEmptySlot(direction, index)) {
                                        _data[index.first][index.second - 1] = SlotType::MoveAllowed;
                                        return;
                                }
                                
                                if (!isEmptySlot(direction, index) && isEmptySlot(direction, { index.first, index.second - 1 })) {
                                        _data[index.first][index.second - 2] = SlotType::MoveAllowed;
                                        markSlotsForMove(direction, { index.first, index.second - 2 }, true);
                                }
                        }

                default:
                        break;
        }
}

bool GameField::isEmptySlot(Direction direction, std::pair<int, int> index) const {

        switch (direction) {
                case Direction::Right:
                        return index.first < Size - 1 && _data[index.first + 1][index.second] == SlotType::Empty;
                case Direction::Left:
                        return index.first > 0 && _data[index.first - 1][index.second] == SlotType::Empty;
                case Direction::Bottom:
                        return index.second < Size - 1 && _data[index.first][index.second + 1] == SlotType::Empty;
                case Direction::Top:
                        return index.second > 0 && _data[index.first][index.second - 1] == SlotType::Empty;
                default:
                        return false;
        }
}