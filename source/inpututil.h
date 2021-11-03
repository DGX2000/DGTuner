#ifndef INPUTUTIL_H
#define INPUTUTIL_H

#include <chrono>
#include <cmath>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include <SFML/Audio.hpp>

class InputUtil
{
public:
    InputUtil() = delete;

    static std::vector<std::string> getAllInputs()
    {
        return sf::SoundRecorder::getAvailableDevices();
    }

    static double getVolumeOfInput(const std::string& input)
    {
        auto recorder = sf::SoundBufferRecorder();
        recorder.setDevice(input);

        recorder.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        recorder.stop();

        // TODO: Move to VolumeUtil
        const auto& buffer = recorder.getBuffer();
        auto volume = double{0.0};
        for(sf::Uint64 i = 0; i < buffer.getSampleCount(); ++i)
        {
            volume += buffer.getSamples()[i] * buffer.getSamples()[i];
        }

        return std::sqrt(volume / static_cast<double>(buffer.getSampleCount()));
    }

    static std::vector<std::pair<std::string, double>> getAllInputsWithVolumes()
    {
        auto inputs = getAllInputs();
        auto inputVolumePairs = std::vector<std::pair<std::string, double>>();

        for(const auto& input : inputs)
        {
            // TODO: Spawn threads for these
            inputVolumePairs.emplace_back(std::pair(input, getVolumeOfInput(input)));
        }

        return inputVolumePairs;
    }

    static std::string getLoudestInput()
    {
        auto inputVolumePairs = getAllInputsWithVolumes();

        auto maxVolumePair =
            std::max_element(inputVolumePairs.begin(), inputVolumePairs.end(),
            [](const auto& lhs, const auto& rhs)
            {
                return lhs.second < rhs.second;
            });

        return maxVolumePair->first;
    }
};

#endif // INPUTUTIL_H
