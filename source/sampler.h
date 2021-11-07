#ifndef SAMPLER_H
#define SAMPLER_H

#include <atomic>
#include <cstdint>
#include <limits>

#include <SFML/Audio.hpp>

#include "medianfilter.h"

class Sampler : public sf::SoundRecorder
{
public:
    Sampler(sf::Time samplingPeriod);

    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) override;
    std::uint64_t getCurrentlyDetectedPeriod() const;

private:
    bool areThereSamplesToSkip() const;
    bool areThereSamplesToFilter() const;
    void startSkippingSamples(std::uint64_t samplesToSkip);
    void startFilteringSamples(std::uint64_t samplesToFilter);
    void skipSample();
    void filterSample(const sf::Int16 *samples, std::size_t sampleCount);

    void trackVolume(const sf::Int16 *samples, std::size_t sampleCount);
    bool soundDetected() const;
    bool soundFadedOut() const;
    void updateVolumeThreshold();
    void resetVolumeThreshold();

private:
    static constexpr std::uint64_t SAMPLES_TO_FILTER = 5;
    static constexpr std::uint64_t SAMPLES_TO_SKIP = 10;

    static constexpr double VOLUME_DETECTION_THRESHOLD = 2.0;
    static constexpr double VOLUME_FADEOUT_THRESHOLD = 0.25;

    static constexpr std::uint64_t PERIOD_LENGTH_AT_START = 250;

    static constexpr std::uint64_t BROAD_SCANNING_RANGE_MIN = 100;
    static constexpr std::uint64_t BROAD_SCANNING_RANGE_MAX = 550;

    static constexpr std::uint64_t FOCUSED_SCANNING_RANGE_HALFWIDTH = 10;

private:
    MedianFilter<std::uint64_t, SAMPLES_TO_FILTER> medianFilter;

    std::atomic<std::uint64_t> currentlyDetectedPeriod;

    std::uint64_t scanningRangeMin{0};
    std::uint64_t scanningRangeMax{0};

    std::uint64_t samplesToSkip{0};
    std::uint64_t samplesToFilter{0};

    double volume{0.0};
    double previousVolume{0.0};
    double volumeThreshold{std::numeric_limits<double>::infinity()};
};

#endif // SAMPLER_H
