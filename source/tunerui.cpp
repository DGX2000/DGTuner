#include "tunerui.h"

#include <string>

// TODO: Remove this include once frequency conversion happens in TuningMediator
#include "audioutil.h"

TunerUi::TunerUi(unsigned int width, unsigned int height)
{
    font.loadFromFile("fonts/IBMPlexMono-Bold.ttf");
    text.setFont(font);
}

void TunerUi::drawOnto(sf::RenderWindow& window)
{
    text.setPosition(20.0F, 100.0F);
    text.setString("Period Length");
    window.draw(text);

    text.setPosition(40.0F, 140.0F);
    text.setString(std::to_string(periodLength));
    window.draw(text);

    text.setPosition(20.0F, 200.0F);
    text.setString("Frequency");
    window.draw(text);

    text.setPosition(40.0F, 240.0F);
    text.setString(std::to_string(AudioUtil::periodToFrequency(periodLength, 44100u)));
    window.draw(text);
}
