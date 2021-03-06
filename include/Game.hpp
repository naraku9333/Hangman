#ifndef SV_HANGMAN_GAME_HPP
#define SV_HANGMAN_GAME_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <ResMan.hpp>
#include <Body.hpp>

namespace sv
{
    enum class State { Play, Win, Lose, Quit };

    class Game
    {
        sf::RenderWindow window;
        ResMan<sf::Texture> textures;
        ResMan<sf::Font> fonts;

        const std::string letters = "abcdefghijklmnopqrstuvwxyz";
        std::string out_letters;
        std::string correct_word, out_word;
        char guess = '\0';

        sf::Text output;

        Body body;
        State state;

    public:       
        Game();
        void Render();
        void Update();
        void Run();
    };
}
#endif
