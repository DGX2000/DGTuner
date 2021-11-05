#ifndef TUNERUI_H
#define TUNERUI_H

#include <SFML/Graphics.hpp>

class TunerUi
{
public:
    TunerUi(unsigned int width, unsigned int height);

    void drawOnto(sf::RenderWindow& window);

    // TODO: Once TuningMediator is finished, this class should receive a frequency instead
    std::uint64_t periodLength{0};

private:
    // TODO: Remove these once the UI is finished
    sf::Font font;
    sf::Text text;
};

#endif // TUNERUI_H
