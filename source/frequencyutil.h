#ifndef FREQUENCYUTIL_H
#define FREQUENCYUTIL_H

#include <cstdint>
#include <tuple>

class FrequencyUtil
{
public:
    struct Signal
    {
        const std::int16_t* samples;
        const std::uint64_t length;
    };

    using Shift = std::uint64_t;
    using PeriodLength = std::uint64_t;

    struct PeriodLengthRange
    {
        PeriodLength min;
        PeriodLength max;
    };

public:
    FrequencyUtil() = delete;

    static std::tuple<PeriodLength, double> detectFundamentalPeriodLength(
            const Signal& signal,
            const PeriodLengthRange& range)
    {
        double maxAutocorrelation{0.0};
        PeriodLength maxPeriodLength{0};

        for(auto shift = range.min; shift < range.max; ++shift)
        {
            auto currentAutocorrelation = autocorrelation(signal, shift);

            if(currentAutocorrelation > maxAutocorrelation)
            {
                maxPeriodLength = shift;
                maxAutocorrelation = currentAutocorrelation;
            }
        }

        return {maxPeriodLength, maxAutocorrelation};
    }

private:
    static double autocorrelation(const Signal& signal, const Shift shift)
    {
        double result = 0.0;

        for(auto i = shift; i < signal.length; ++i)
        {
            result += signal.samples[i] * signal.samples[i - shift];
        }

        return result / static_cast<double>(signal.length - shift);
    }
};

#endif // FREQUENCYUTIL_H
