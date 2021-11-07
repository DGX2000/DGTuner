#ifndef SAMPLER_H
#define SAMPLER_H

#include <atomic>
#include <cstdint>

#include <SFML/Audio.hpp>

#include "medianfilter.h"

class Sampler : public sf::SoundRecorder
{
public:
    Sampler(sf::Time samplingPeriod);

    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) override;
    std::uint64_t getCurrentlyDetectedPeriod() const;

private:
    MedianFilter<5> medianFilter;

    std::atomic<std::uint64_t> currentlyDetectedPeriod;

    std::uint64_t scanningRangeMin{0};
    std::uint64_t scanningRangeMax{550};

    std::uint64_t samplesToSkip{0};
    std::uint64_t samplesToFilter{0};

    double previousVolume{0.0};
    // TODO: Make this infinity
    double dynamicThreshold{70000.0};
};

#endif // SAMPLER_H
