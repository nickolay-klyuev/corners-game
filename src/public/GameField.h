#pragma once

#include <array>
#include <vector>

enum class Direction {
        Top,
        Bottom,
        Left,
        Right
};

enum SlotType {
        Empty = 0,
        WhitePawn = 1,
        BlackPawn = 2,
        MoveAllowed = 3,
        WhitePawnSelected = 4,
        BlackPawnSelected = 5
};

/* This class is independant and contains all and only game field data. */
class GameField {
public:
        static constexpr int Size = 8;

        // Used by Render class to know if it has to be redrawed
        bool IsDirtyFlag = false;
        bool IsPawnsDirtyFlag = false;

private:
        std::array<std::array<int, Size>, Size> _data = {{
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
                { 0, 0, 0, 0, 0, 2, 2, 2 },
        }};

        std::pair<int, int> _selected = { -1, -1 };

public:
        GameField() = default;
        ~GameField() = default;

        int operator[](std::pair<int, int> index) const {
                return _data[index.first][index.second];
        }

        int& operator[](std::pair<int, int> index) {
                return _data[index.first][index.second];
        }

        const auto& GetData() const {
                return _data;
        }

        auto GetWhitesIndexes() const -> std::vector<std::pair<int, int>>;

        void UnselectAll();

        void Select(std::pair<int, int> index);

        bool CanBeMovedRightBottom(std::pair<int, int> index) const;
        bool CanBeMovedRight(std::pair<int, int> index) const;
        bool CanBeMovedBottom(std::pair<int, int> index) const;

        bool MoveIfPossible(std::pair<int, int> index);

        void Log() const;

private:
        void markSlotsForMove(Direction, std::pair<int, int> index, bool jump_check = false);
        bool isEmptySlot(Direction, std::pair<int, int>) const;
};