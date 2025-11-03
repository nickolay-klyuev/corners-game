#include "Renderer.h"

#include <iostream>

Renderer::Renderer(GameField<>* gameField_ptr, sf::RenderWindow* window_ptr)
        : _gameField_ptr(gameField_ptr), _window_ptr(window_ptr) {
        /*for (int i = 0; i < slots.size(); ++i) {
                for (int j = 0; j < slots[i].size(); ++j) {
                        sf::Sprite slotSprite(streamer_ptr->Get(TextureStreamer::TextureType::BlackSlot));
                        slotSprite.setPosition({ 100.f * i, 100.f * j });
                        slotSprite.setScale({ 0.4f, 0.4f });
                        _sprites.push_back(slotSprite);
                }
        }*/

        const auto& data = _gameField_ptr->GetData();

        for (int i = 0; i < data.size(); ++i) {
                ChangeFlipFlopFlag();

                for (int j = 0; j < data[i].size(); ++j) {
                        sf::Sprite new_sprite(GetSlotTexture_FlipFlop());

                        auto size = new_sprite.getLocalBounds().size;
                        new_sprite.setScale({ 50.f / size.x, 50.f / size.y });
                        new_sprite.setPosition({55.f * i, 55.f * j });

                        _renderingSlotSprites.push_back(new_sprite);
                        _renderingSlotMap.insert({{i, j}, new_sprite});

                        if (data[i][j] != 0) {
                                if (data[i][j] == 1) {
                                        new_sprite.setTexture(_textureStreamer.Get(TextureStreamer::TextureType::WhitePawn));
                                        //sf::Sprite pawn_sprite(_textureStreamer.Get(TextureStreamer::TextureType::WhitePawn));
                                } else {
                                        //sf::Sprite pawn_sprite(_textureStreamer.Get(TextureStreamer::TextureType::BlackPawn));
                                        new_sprite.setTexture(_textureStreamer.Get(TextureStreamer::TextureType::BlackPawn));
                                }

                                auto size = new_sprite.getLocalBounds().size;
                                new_sprite.setScale({ 50.f / size.x, 50.f / size.y });
                                new_sprite.setPosition({ 55.f * i, 55.f * j });

                                _renderingPawnSprites.push_back(new_sprite);
                                _renderingPawnMap.insert({{i, j}, new_sprite});
                        }
                }
        }

        /*const auto& slots = _gameField_ptr->GetSlots();

        for (int i = 0; i < slots.size(); ++i) {
                ChangeFlipFlopFlag();

                for (int j = 0; j < slots[i].size(); ++j) {
                        sf::Sprite new_sprite(GetSlotTexture_FlipFlop());

                        auto size = new_sprite.getLocalBounds().size;
                        new_sprite.setScale({ 50.f / size.x, 50.f / size.y });
                        new_sprite.setPosition({55.f * i, 55.f * j });

                        _renderingSlotSprites.push_back(new_sprite);

                        if (const Pawn* pawn = slots[i][j].HoldingPawn_ptr) {
                                if (pawn->Team == Pawn::TeamType::White) {
                                        new_sprite.setTexture(_textureStreamer.Get(TextureStreamer::TextureType::WhitePawn));
                                        //sf::Sprite pawn_sprite(_textureStreamer.Get(TextureStreamer::TextureType::WhitePawn));
                                } else {
                                        //sf::Sprite pawn_sprite(_textureStreamer.Get(TextureStreamer::TextureType::BlackPawn));
                                        new_sprite.setTexture(_textureStreamer.Get(TextureStreamer::TextureType::BlackPawn));
                                }

                                auto size = new_sprite.getLocalBounds().size;
                                new_sprite.setScale({ 50.f / size.x, 50.f / size.y });
                                new_sprite.setPosition({ 55.f * i, 55.f * j });

                                _renderingPawnSprites.push_back(new_sprite);
                        }
                }
        }*/

}

void Renderer::Render() {
        _window_ptr->clear();

        if (_gameField_ptr->IsDirtyFlag) {
                const auto& data = _gameField_ptr->GetData();
                
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

        /*for (const auto& slot_sprite : _renderingSlotSprites) {
                _window_ptr->draw(slot_sprite);
        }*/

        for (const auto& [index, slot_sprite] : _renderingSlotMap) {
                _window_ptr->draw(slot_sprite);
        }

        for (const auto& [index, pawn_sprite] : _renderingPawnMap) {
                _window_ptr->draw(pawn_sprite);
        }

        /*for (const auto& pawn_sprite : _renderingPawnSprites) {
                _window_ptr->draw(pawn_sprite);
        }*/

        _window_ptr->display();
}

const sf::Texture& Renderer::GetSlotTexture_FlipFlop() {
        ChangeFlipFlopFlag();

        if (_flipFlopFlag) {
                return _textureStreamer.Get(TextureStreamer::TextureType::WhiteSlot);
        }

        return _textureStreamer.Get(TextureStreamer::TextureType::BlackSlot);
}