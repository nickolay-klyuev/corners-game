#include "Renderer.h"

#include <iostream>

Renderer::Renderer(GameField* gameField_ptr, sf::RenderWindow* window_ptr)
        : _gameField_ptr(gameField_ptr), _window_ptr(window_ptr) {
        const auto& data = _gameField_ptr->GetData();

        for (int i = 0; i < data.size(); ++i) {
                reverseFlipFlopFlag();

                for (int j = 0; j < data[i].size(); ++j) {
                        sf::Sprite new_sprite(getSlotTexture_FlipFlop());

                        auto sprite_size = new_sprite.getLocalBounds().size;
                        new_sprite.setScale({ SlotSize / sprite_size.x, SlotSize / sprite_size.y });
                        new_sprite.setPosition({SlotSizeWithPadding * i, SlotSizeWithPadding * j });

                        _renderingSlotMap.insert({{i, j}, new_sprite});

                        if (data[i][j] != SlotType::Empty) {
                                if (data[i][j] == SlotType::WhitePawn) {
                                        new_sprite.setTexture(_textureStreamer[TextureType::WhitePawn]);
                                } else {
                                        new_sprite.setTexture(_textureStreamer[TextureType::BlackPawn]);
                                }

                                auto size = new_sprite.getLocalBounds().size;
                                new_sprite.setScale({ SlotSize / size.x, SlotSize / size.y });
                                new_sprite.setPosition({ SlotSizeWithPadding * i, SlotSizeWithPadding * j });

                                _renderingPawnMap.insert({{i, j}, new_sprite});
                        }
                }
        }
}

void Renderer::Render() {
        _window_ptr->clear();
        
        const auto& data = _gameField_ptr->GetData();

        if (_gameField_ptr->IsDirtyFlag) {
                
                for (int i = 0; i < data.size(); ++i) {
                        for (int j = 0; j < data[i].size(); ++j) {
                                if (_renderingPawnMap.find({ i, j }) == _renderingPawnMap.end()) {
                                        auto& slot = _renderingSlotMap.at({ i, j });

                                        if (data[i][j] == 3) {
                                                slot.setColor(sf::Color::Green);
                                        }
                                        else {
                                                slot.setColor(sf::Color::White);
                                        }

                                        continue;
                                }

                                auto& pawn = _renderingPawnMap.at({ i, j });

                                if (data[i][j] == 1 || data[i][j] == 2) {
                                        pawn.setColor(sf::Color::White);
                                } else if (data[i][j] == 4 || data[i][j] == 5) {
                                        pawn.setColor(sf::Color::Blue);
                                }
                        }
                }

                _gameField_ptr->IsDirtyFlag = false;
        }

        if (_gameField_ptr->IsPawnsDirtyFlag) {
                _gameField_ptr->IsPawnsDirtyFlag = false;

                _renderingPawnMap.clear();

                for (int i = 0; i < data.size(); ++i) {
                        for (int j = 0; j < data[i].size(); ++j) {
                                if (data[i][j] == 1 || data[i][j] == 2 || data[i][j] == 4 || data[i][j] == 5) {
                                        sf::Sprite new_sprite(_textureStreamer[TextureType::BlackPawn]);

                                        if (data[i][j] == 1 || data[i][j] == 4) {
                                                new_sprite.setTexture(_textureStreamer[TextureType::WhitePawn]);
                                        } 

                                        auto size = new_sprite.getLocalBounds().size;
                                        new_sprite.setScale({ SlotSize / size.x, SlotSize / size.y });
                                        new_sprite.setPosition({ SlotSizeWithPadding * i, SlotSizeWithPadding * j });

                                        _renderingPawnMap.insert({{i, j}, new_sprite});
                                }
                        }
                }

        }

        for (const auto& [index, slot_sprite] : _renderingSlotMap) {
                _window_ptr->draw(slot_sprite);
        }

        for (const auto& [index, pawn_sprite] : _renderingPawnMap) {
                _window_ptr->draw(pawn_sprite);
        }

        _window_ptr->display();
}

const sf::Texture& Renderer::getSlotTexture_FlipFlop() {
        reverseFlipFlopFlag();

        if (_flipFlopFlag) {
                return _textureStreamer[TextureType::WhiteSlot];
        }

        return _textureStreamer[TextureType::BlackSlot];
}