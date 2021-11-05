#ifndef SAMPLER_H
#define SAMPLER_H

#include <atomic>
#include <cstdint>

#include <SFML/Audio.hpp>

class Sampler : public sf::SoundRecorder
{
public:
    Sampler(sf::Time samplingPeriod);

    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) override;
    std::uint64_t getCurrentlyDetectedPeriod() const;

private:
    std::atomic<std::uint64_t> currentlyDetectedPeriod;
};

#endif // SAMPLER_H
