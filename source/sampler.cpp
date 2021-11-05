#include "sampler.h"

#include "audioutil.h"

Sampler::Sampler(sf::Time time)
    : currentlyDetectedPeriod(250)
{
    setProcessingInterval(time);
}

bool Sampler::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount)
{
    // TODO: First idea for algorithm
    // (1) High volume threshold as first filter, if volume threshhold is passed, scan the whole
    //     range and detect the fundamental period (threshold has to be dynamic)
    // (2) Medium volume threshold => as long as volume is above this look in the range
    //     found in (1)
    // (3) Low volume threshold => no scanning in this region, but volume threshold is lowered every
    //     interval we're in this region
    auto periodCorrelationPair =
            AudioUtil::detectFundamentalPeriodLength(AudioUtil::Signal{samples, sampleCount},
                                                     AudioUtil::PeriodLengthRange{100, 550});

    if(periodCorrelationPair.second > 5000.0)
    {
        auto min = periodCorrelationPair.first - 10;
        auto max = periodCorrelationPair.first + 10;
        periodCorrelationPair =
                AudioUtil::detectFundamentalPeriodLength(AudioUtil::Signal{samples, sampleCount},
                                                       AudioUtil::PeriodLengthRange{min, max});

        currentlyDetectedPeriod.store(periodCorrelationPair.first);
    }

    return true;
}

uint64_t Sampler::getCurrentlyDetectedPeriod() const
{
    return currentlyDetectedPeriod.load();
}
