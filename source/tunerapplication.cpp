#include "tunerapplication.h"

TunerApplication::TunerApplication()
    : window(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)),
      ui(new TunerUi(WINDOW_WIDTH, WINDOW_HEIGHT)),
      tuningMediator(new TuningMediator())
{
    window.setFramerateLimit(60);

    // TODO: Handle window resizing
}

void TunerApplication::run()
{
    while(window.isOpen())
    {
        handleEvents();

        ui->periodLength = tuningMediator->getFundamentalFrequency();

        display();
    }
}

void TunerApplication::handleEvents()
{
    sf::Event event{};

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            break;
        default:
            break;
        }
    }
}

void TunerApplication::display()
{
    window.clear();
    ui->drawOnto(window);
    window.display();
}

