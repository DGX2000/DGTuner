#include "sampler.h"

#include "audioutil.h"

// TODO: Remove iostream (only for debugging)
#include <iostream>

Sampler::Sampler(sf::Time time)
    : currentlyDetectedPeriod(250)
{
    setProcessingInterval(time);
}

bool Sampler::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount)
{
    // TODO: Clean this mess up, also clean up medianfilter.h in the process
    // TODO: periodCorrelationPair does not need to be a pair anymore
    // TODO: Figure out why it sometime returns periodLength = 0
    // Get volume and change in volume as a ratio
    auto volume = AudioUtil::computeRmsVolume(AudioUtil::Signal{samples, sampleCount});
    auto volumeChange = volume / previousVolume;
    previousVolume = volume;

    // TODO: Make 2.0 a named constant
    if(samplesToFilter == 0 && samplesToSkip == 0)
    {
        if(volumeChange > 2.0)
        {
            dynamicThreshold = volume;
            samplesToSkip = 10;
        }
        else if(volume > 0.25 * dynamicThreshold)
        {
            auto median = medianFilter.getMedian();
            scanningRangeMin = median - 10;
            scanningRangeMax = median + 10;

            // TODO: Make 0.25 a named constant
            auto periodCorrelationPair =
                AudioUtil::detectFundamentalPeriodLength(AudioUtil::Signal{samples, sampleCount},
                                                         AudioUtil::PeriodLengthRange{scanningRangeMin, scanningRangeMax});

            currentlyDetectedPeriod.store(periodCorrelationPair.first);
        }
        else
        {
            // Reset dynamic threshold
            dynamicThreshold = 70000.0;
        }
    }
    else
    {
        if(samplesToSkip == 0)
        {
            --samplesToFilter;
            auto periodCorrelationPair =
                AudioUtil::detectFundamentalPeriodLength(AudioUtil::Signal{samples, sampleCount},
                                                         AudioUtil::PeriodLengthRange{100, 550});
            medianFilter.update(periodCorrelationPair.first);
        }
        else
        {
            --samplesToSkip;
            if(samplesToSkip == 0)
            {
                samplesToFilter = 5;
            }
        }
    }

    return true;
}

uint64_t Sampler::getCurrentlyDetectedPeriod() const
{
    return currentlyDetectedPeriod.load();
}
