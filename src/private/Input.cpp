#include "Input.h"

void Input::OnMouseLeftClicked(sf::Vector2f mouse_position) {
        if (IsWaitingForEnemyMove) {
                return;
        }

        for (const auto& [index, sprite] : _renderer_ptr->GetRenderingPawnMap()) {
                if ((*_gameField_ptr)[index] == SlotType::WhitePawn) { // White pawns are enemies'
                        continue;
                }
                
                if (sprite.getGlobalBounds().contains(mouse_position)) {
                        _gameField_ptr->Select(index);
                }
        }

        for (const auto& [index, slot_sprite] : _renderer_ptr->GetRenderingSlotMap()) {
                if (slot_sprite.getGlobalBounds().contains(mouse_position)) {
                        IsWaitingForEnemyMove = _gameField_ptr->MoveIfPossible(index);
                }
        }
}