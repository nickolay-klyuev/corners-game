#include <cstdlib>
#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"

#include "GameField.h"
#include "Renderer.h"
#include "TextureStreamer.h"
#include "Input.h"
#include "AIEnemy.h"

int main(int argc, char const *argv[]) {

        TextureStreamer ts;

        sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Corners Game");

        auto texture_streamer = std::make_unique<TextureStreamer>();
        auto game_field_ptr = std::make_unique<GameField<>>(texture_streamer.get());
        auto slots = game_field_ptr->GetSlots();

        auto renderer_ptr = std::make_unique<Renderer>(game_field_ptr.get(), &window);

        auto input = std::make_unique<Input>(renderer_ptr.get(), game_field_ptr.get());

        auto ai_enemy = std::make_unique<AIEnemy>(input.get(), game_field_ptr.get());

        while (window.isOpen()) {
                while (const std::optional event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) {
                                window.close();
                        } else if (event->is<sf::Event::MouseButtonPressed>()) {
                                input->OnMouseLeftClicked(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                        }
                }

                ai_enemy->Update();

                renderer_ptr->Render();
        }

        return EXIT_SUCCESS;
}
