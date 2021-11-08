#include "tunerui.h"

#include <string>

// TODO: Remove this include once frequency conversion happens in TuningMediator
#include "audioutil.h"
#include "musicutil.h"

TunerUi::TunerUi(unsigned int width, unsigned int height)
{
    font.loadFromFile("fonts/IBMPlexMono-Bold.ttf");
    text.setFont(font);

    background = sf::RectangleShape(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(128, 128, 128));
}

void TunerUi::drawOnto(sf::RenderWindow& window)
{
    window.draw(background);

    // TODO: This is just for debugging, replace this
    // with the prepared graphical UI asap
    text.setPosition(20.0F, 100.0F);
    text.setString("Period Length");
    window.draw(text);

    text.setPosition(40.0F, 140.0F);
    text.setString(std::to_string(periodLength));
    window.draw(text);

    text.setPosition(20.0F, 180.0F);
    text.setString("Frequency");
    window.draw(text);

    text.setPosition(40.0F, 220.0F);
    auto frequency = AudioUtil::periodToFrequency(periodLength, 44100);
    text.setString(std::to_string(frequency));
    window.draw(text);

    text.setPosition(20.0F, 320.0F);
    text.setString("Closest Note");
    window.draw(text);

    text.setPosition(40.0F, 360.0F);
    auto note = MusicUtil::createNoteFromFrequency(frequency);
    text.setString(note.letter + std::to_string(note.octave));
    window.draw(text);

    text.setPosition(20.0F, 400.0F);
    text.setString("Deviation in Cents");
    window.draw(text);

    text.setPosition(40.0F, 440.0F);
    auto targetNoteFrequency = MusicUtil::getFrequencyOfNote(note);
    auto distanceInCents = MusicUtil::getDistanceBetweenFrequenciesInCents(frequency, targetNoteFrequency);
    text.setString(std::to_string(static_cast<int>(distanceInCents)));
    window.draw(text);
}
