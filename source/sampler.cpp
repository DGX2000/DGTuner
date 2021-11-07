#include "sampler.h"

#include "audioutil.h"

Sampler::Sampler(sf::Time time) : currentlyDetectedPeriod(PERIOD_LENGTH_AT_START)
{
    setProcessingInterval(time);
}

bool Sampler::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount)
{
    trackVolume(samples, sampleCount);

    if(areThereSamplesToFilter())
    {
        filterSample(samples, sampleCount);
    }
    else if(areThereSamplesToSkip())
    {
        skipSample();
        if(!areThereSamplesToSkip())
        {
            startFilteringSamples(SAMPLES_TO_FILTER);
        }
    }
    else
    {
        if(soundDetected())
        {
            updateVolumeThreshold();
            startSkippingSamples(SAMPLES_TO_SKIP);
        }
        else if(!soundFadedOut())
        {
            auto fundamentalPeriodLength =
                AudioUtil::detectFundamentalPeriodLength(AudioUtil::Signal{samples, sampleCount},
                                                         AudioUtil::PeriodLengthRange{scanningRangeMin, scanningRangeMax});
            currentlyDetectedPeriod.store(fundamentalPeriodLength);
        }
        else
        {
            resetVolumeThreshold();
        }
    }

    return true;
}

uint64_t Sampler::getCurrentlyDetectedPeriod() const
{
    return currentlyDetectedPeriod.load();
}

bool Sampler::areThereSamplesToSkip() const
{
    return samplesToSkip != 0;
}

bool Sampler::areThereSamplesToFilter() const
{
    return samplesToFilter != 0;
}

void Sampler::startSkippingSamples(std::uint64_t samplesToSkip)
{
    this->samplesToSkip = samplesToSkip;
}

void Sampler::startFilteringSamples(std::uint64_t samplesToFilter)
{
    this->samplesToFilter = samplesToFilter;
}

void Sampler::skipSample()
{
    --samplesToSkip;
}

void Sampler::filterSample(const sf::Int16 *samples, std::size_t sampleCount)
{
    --samplesToFilter;

    auto fundamentalPeriodLength =
        AudioUtil::detectFundamentalPeriodLength(
                AudioUtil::Signal{samples, sampleCount},
                AudioUtil::PeriodLengthRange{BROAD_SCANNING_RANGE_MIN, BROAD_SCANNING_RANGE_MAX});
    medianFilter.update(fundamentalPeriodLength);

    if(!areThereSamplesToFilter())
    {
        auto median = medianFilter.getMedian();
        scanningRangeMin = median - FOCUSED_SCANNING_RANGE_HALFWIDTH;
        scanningRangeMax = median + FOCUSED_SCANNING_RANGE_HALFWIDTH;
    }
}

void Sampler::trackVolume(const sf::Int16 *samples, std::size_t sampleCount)
{
    previousVolume = volume;
    volume = AudioUtil::computeRmsVolume(AudioUtil::Signal{samples, sampleCount});
}

bool Sampler::soundDetected() const
{
    return (volume / previousVolume) > VOLUME_DETECTION_THRESHOLD;
}

bool Sampler::soundFadedOut() const
{
    return volume <= VOLUME_FADEOUT_THRESHOLD * volumeThreshold;
}

void Sampler::updateVolumeThreshold()
{
    volumeThreshold = volume;
}

void Sampler::resetVolumeThreshold()
{
    volumeThreshold = std::numeric_limits<double>::infinity();
}
