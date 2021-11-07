#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <array>
#include <algorithm>
#include <atomic>
#include <cctype>
#include <iostream>

template<std::size_t N>
class MedianFilter
{
public:
    std::size_t getMedian()
    {
        auto mediumIterator = pastValues.begin();
        std::advance(mediumIterator, N/2);
        std::nth_element(pastValues.begin(), mediumIterator, pastValues.begin());
        
        return pastValues[N/2];
    }

    void update(int sample)
    {
        pastValues[writerIndex] = sample;
        writerIndex = (writerIndex + 1) % N;
    }

private:
    std::array<std::size_t, N> pastValues{0};
    std::size_t writerIndex{0};
};


#endif // MEDIANFILTER_H
