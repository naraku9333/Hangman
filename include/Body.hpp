#ifndef SV_HANGMAN_BODY_HPP
#define SV_HANGMAN_BODY_HPP

#include <vector>
#include <SFML/Graphics.hpp>

namespace sv
{
    class Body : public sf::Drawable
    {
        class part : public sf::Drawable
        {
            sf::Sprite img;

            public:

            part(const sf::Texture&, const sf::IntRect, const sf::Vector2f);

            virtual ~part() {}

            void draw(sf::RenderTarget&, sf::RenderStates) const;
        };

        int parts_to_draw;
        std::vector<part> parts;

        public:        

        Body(const sf::Texture&);

        void draw(sf::RenderTarget&, sf::RenderStates) const;

        void operator++(){ ++parts_to_draw; }

        bool dead() const { return parts_to_draw == parts.size(); }

        void alive() { parts_to_draw = 0; }
    };
}
#endif
