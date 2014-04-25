#include <Body.hpp>

namespace sv
{
    Body::part::part(const sf::Texture& tex, const sf::IntRect rect, sf::Vector2f pos) :
        img(tex, rect)
    {
        img.setPosition(pos);
    }

    void Body::part::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(img);
    }

    Body::Body(const sf::Texture& tex) :
        parts_to_draw(0),
        parts({ { tex, sf::IntRect(0, 0, 84, 152), { 367, 94 } },
                { tex, sf::IntRect(84, 0, 84, 152), { 365, 195 } },
                { tex, sf::IntRect(168, 0, 84, 152), { 300, 195 } },
                { tex, sf::IntRect(252, 0, 84, 152), { 435, 190 } },
                { tex, sf::IntRect(336, 0, 84, 152), { 350, 300 } },
                { tex, sf::IntRect(420, 0, 84, 152), { 400, 300 } } })
    {

    }

    void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (parts_to_draw <= parts.size())
        {
            for (int i = 0; i < parts_to_draw; ++i)
            {
                target.draw(parts[i]);
            }
        }
    }    
}
