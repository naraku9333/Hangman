#include <Game.hpp>
#include <Utility.hpp>
#include <cctype>

namespace sv
{
    Game::Game() : 
        window({ 800, 700 }, "Hangman"),
        textures(), fonts(),
        out_letters(letters),
        output("", fonts.get("res/Sansation.ttf"), 50),
        body(textures.get("res/hanged_man_sheet.png")),
        state(State::Play)
    {
        util::init_words(correct_word, out_word);
        window.setFramerateLimit(60);
        output.setPosition(200, 600);
        output.setColor(sf::Color::Blue);
    }

    void Game::Render()
    {
        window.clear();
        window.draw(sf::Sprite(textures.get("res/gallows.png")));
        window.draw(body);

        output.setString(out_word);
        window.draw(output);
        window.draw(sf::Text("\t\t" + out_letters, fonts.get("res/Sansation.ttf")));

        if (state == State::Lose)
            window.draw(sf::Sprite(textures.get("res/lose.png")));
        else if (state == State::Win)
            window.draw(sf::Sprite(textures.get("res/win.png")));

        window.display();
    }

    void Game::Update()
    {
        if (state == State::Play && guess != '\0')
        {
            //remove the list of avialable letters
            if (out_letters.find(::tolower(guess)) != std::string::npos)
                out_letters.replace(::tolower(guess) - 'a', 1, "_");

            auto p = correct_word.begin();
            bool found = false;
            while ((p = std::find_if(p, correct_word.end(), 
                [this](const char c){ return ::tolower(guess) == ::tolower(c); })) != correct_word.end())
            {                    
                found = true;
                out_word[p - correct_word.begin()] = *p;
                ++p;  
                if (out_word == correct_word)
                {
                    state = State::Win;
                    break;
                }
            }                
            if (!found)
            {
                ++body;
                if (body.dead())
                {
                    state = State::Lose;
                    out_word = correct_word;
                }
            }
        }
        else
        {
            if (guess == 'Y' || guess == 'y')
            {
                state = State::Play;//reset state
                body.alive();
                util::init_words(correct_word, out_word);
                out_letters = letters;
            }
            else if (guess == 'N' || guess == 'n') window.close();
        }
        guess = '\0';
    }    

    void Game::Run()
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))//event loop
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::TextEntered:
                        guess = event.text.unicode;
                        break;
                    default:
                        break;
                }
            }
            Update();
            Render();
        }
    }
}
