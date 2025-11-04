#include <cstdlib>
#include <memory>

#include "SFML/Graphics.hpp"

#include "GameField.h"
#include "Renderer.h"
#include "TextureStreamer.h"
#include "Input.h"
#include "AIEnemy.h"

int main(int argc, char const *argv[]) {

        constexpr int window_size = Renderer::SlotSizeWithPadding * GameField::Size - Renderer::SlotPaddingSize;
        sf::RenderWindow window(sf::VideoMode({ window_size, window_size }), "Corners Game", sf::Style::Titlebar | sf::Style::Close);

        auto game_field_ptr = std::make_unique<GameField>();
        auto renderer_ptr = std::make_unique<Renderer>(game_field_ptr.get(), &window);
        auto input_ptr = std::make_unique<Input>(renderer_ptr.get(), game_field_ptr.get());
        auto ai_enemy_ptr = std::make_unique<AIEnemy>(input_ptr.get(), game_field_ptr.get());

        while (window.isOpen()) {
                while (const std::optional event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) {
                                window.close();
                        } else if (event->is<sf::Event::MouseButtonPressed>()) {
                                input_ptr->OnMouseLeftClicked(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                        }
                }

                ai_enemy_ptr->Update();

                renderer_ptr->Render();
        }

        return EXIT_SUCCESS;
}
