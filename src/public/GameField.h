#pragma once

#include <array>
#include <iostream>
#include <vector>
#include <deque>

#include "TextureStreamer.h"

struct Pawn {
        enum class TeamType {
                White,
                Black
        };

        TeamType Team;

        Pawn(TeamType team) : Team(team) {}
        ~Pawn() = default;
};

enum class Direction {
        Top,
        Bottom,
        Left,
        Right
};

struct Slot {
        Pawn* HoldingPawn_ptr = nullptr;

        Slot* Top_ptr = nullptr;
        Slot* Bottom_ptr = nullptr;
        Slot* Left_ptr = nullptr;
        Slot* Right_ptr = nullptr;

        template <Direction D>
        Slot* Get() {
                if constexpr (std::is_same_v<D, Direction::Top>) {
                        return Top_ptr;
                } else if constexpr (std::is_same_v<D, Direction::Bottom>) {
                        return Bottom_ptr;
                } else if constexpr (std::is_same_v<D, Direction::Left>) {
                        return Left_ptr;
                } else {
                        return Right_ptr;
                }
        }

        template <Direction D>
        void Move() {
                if (!HoldingPawn_ptr) {
                        // Slot doesn't have a pawn
                        return;
                }

                move<D>(this, Get<D>());
        }

private:
        template <Direction D>
        void move(Slot* from_ptr, Slot* to_ptr) {
                if (!from_ptr || !to_ptr) {
                        return;
                }

                if (to_ptr->HoldingPawn_ptr) {
                        // Destonation slot already has a pawn, so we can jump
                        move<D>(from_ptr, to_ptr->Get<D>());
                        return;
                }

                std::swap(from_ptr->HoldingPawn_ptr, to_ptr->HoldingPawn_ptr);
        }
};

#define WHITE 1
#define EMPTY 0
#define BLACK 2
#define CAN_MOVE 3
#define WHITE_SELECTED 4
#define BLACK_SELECTED 5

/* This class contains all game field data. It's independant and can be used with any framework. */
template <unsigned int FIELD_SIZE = 8, unsigned int PAWNS_AMOUNT = 9>
class GameField {
        std::array<std::array<Slot, FIELD_SIZE>, FIELD_SIZE> _slots;
        std::deque<Pawn> _pawns;

        std::vector<std::vector<int>> _data = {
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
        };

        std::pair<int, int> _selected = { -1, -1 };

public:
        // Used by Render class to know if it has to be redrawed
        bool IsDirtyFlag = false;
        bool IsPawnsDirtyFlag = false;

        auto GetData() const -> const std::vector<std::vector<int>>& {
                return _data;
        }

        auto GetWhitesIndexes() const -> std::vector<std::pair<int, int>> {
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

        void UnselectAll() {
                for (auto& data_column : _data) {
                        for (auto& slot : data_column) {
                                if (slot == 3) {
                                        slot = 0;
                                } else if (slot == 4) {
                                        slot = 1;
                                } else if (slot == 5) {
                                        slot = 2;
                                }
                        }
                }

                _selected = { -1, -1 };
        }

        void Select(std::pair<int, int> index) {
                UnselectAll();

                if (_data[index.first][index.second] == 2 || _data[index.first][index.second] == 1) {
                        if (_data[index.first][index.second] == 2) {
                                _data[index.first][index.second] = 5;
                        } else if (_data[index.first][index.second] == 1) {
                                _data[index.first][index.second] = 4;
                        }

                        IsDirtyFlag = true;

                        _selected = index;
                }

                if (index.first < 7 && _data[index.first + 1][index.second] == 0) {
                        _data[index.first + 1][index.second] = 3;
                }

                if (index.first > 0 && _data[index.first - 1][index.second] == 0) {
                        _data[index.first - 1][index.second] = 3;
                }

                if (index.second < 7 && _data[index.first][index.second + 1] == 0) {
                        _data[index.first][index.second + 1] = 3;
                }

                if (index.second > 0 && _data[index.first][index.second - 1] == 0) {
                        _data[index.first][index.second - 1] = 3;
                }
        }

        bool CanBeMovedSomewhere(std::pair<int, int> index) const {
                return (index.first < 7 && _data[index.first + 1][index.second]) == 0 ||
                        (index.first > 0 && _data[index.first - 1][index.second]) == 0 ||
                        (index.second < 7 && _data[index.first][index.second + 1]) == 0 ||
                        (index.second > 0 && _data[index.first][index.second - 1]) == 0;
        }

        bool CanBeMovedRightBottom(std::pair<int, int> index) const {
                return (index.first < 7 && _data[index.first + 1][index.second]) == 0 ||
                        (index.second < 7 && _data[index.first][index.second + 1] == 0);
        }

        bool CanBeMovedRight(std::pair<int, int> index) const {
                return index.first < 7 && (_data[index.first + 1][index.second] == 3);
        }

        bool CanBeMovedBottom(std::pair<int, int> index) const {
                return index.second < 7 && (_data[index.first][index.second + 1] == 3);
        }

        bool MoveIfPossible(std::pair<int, int> index) {
                if (_data[index.first][index.second] == 3) {
                        std::swap(_data[_selected.first][_selected.second], _data[index.first][index.second]);

                        IsDirtyFlag = true;
                        IsPawnsDirtyFlag = true;

                        UnselectAll();

                        return true;
                }

                return false;
        }

        void Log() {
                for (auto t : _data) {
                        for (auto a : t) {
                                std::cout << a << " ";
                        }
                        std::cout << '\n';
                }
        }

public:
        GameField() = delete;
        GameField(TextureStreamer* streamer_ptr) {
                for (int i = 0; i < FIELD_SIZE; ++i) {
                        for (int j = 0; j < FIELD_SIZE; ++j) {

                                if (i < 3 && j < 3) {
                                        _slots[i][j].HoldingPawn_ptr = &_pawns.emplace_back(Pawn::TeamType::White);
                                }

                                if (i >= FIELD_SIZE - 3 && j >= FIELD_SIZE - 3) {
                                        _slots[i][j].HoldingPawn_ptr = &_pawns.emplace_back(Pawn::TeamType::Black);
                                }

                                if (i > 0) {
                                        _slots[i][j].Top_ptr = &_slots[i - 1][j];
                                }

                                if (i < FIELD_SIZE - 1) {
                                        _slots[i][j].Bottom_ptr = &_slots[i + 1][j];
                                }

                                if (j > 0) {
                                        _slots[i][j].Left_ptr = &_slots[i][j - 1];
                                }

                                if (j < FIELD_SIZE - 1) {
                                        _slots[i][j].Right_ptr = &_slots[i][j + 1];
                                }
                        }
                }
        }
        ~GameField() = default;

        int operator[](std::pair<int, int> index) const {
                return _data[index.first][index.second];
        }

        /*auto GetSlots() const -> const std::array<std::array<Slot, FIELD_SIZE>, FIELD_SIZE>& {
                return _slots;
        }*/

        auto GetSlots() const -> const std::array<std::array<Slot, FIELD_SIZE>, FIELD_SIZE>& {
                return _slots;
        }
};