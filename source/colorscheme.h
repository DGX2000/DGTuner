#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <unordered_map>
#include <string>

#include <SFML/Graphics/Color.hpp>

sf::Color COLOR_BACKGROUND = sf::Color(192, 203, 220);
sf::Color COLOR_OUTLINE = sf::Color(0, 0, 0);
sf::Color COLOR_OPTIONS = sf::Color(104, 56, 108);
sf::Color COLOR_SLIDING_BAND = sf::Color(58, 68, 102);
sf::Color COLOR_SLIDING_BAND_WINDOW = sf::Color(139, 155, 180);

sf::Color COLOR_TEXT = sf::Color(255, 255, 255);
sf::Color COLOR_TEXT_INACTIVE = sf::Color(139, 155, 180);

sf::Color COLOR_ACCENT = sf::Color(44, 232, 245);
sf::Color COLOR_ACCENT_TRANSLUCENT = sf::Color(44, 232, 245, 64);

sf::Color COLOR_NO_VOLUME = sf::Color(139, 155, 180);
sf::Color COLOR_LOW_VOLUME = sf::Color(62, 137, 72);
sf::Color COLOR_MID_VOLUME = sf::Color(254, 174, 52);
sf::Color COLOR_HIGH_VOLUME = sf::Color(228, 59, 68);

#endif // COLORSCHEME_H
