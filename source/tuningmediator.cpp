#include "tuningmediator.h"

TuningMediator::TuningMediator()
{
    // 1) Pick loudest input
    // 2) convert Frequency Range
    //    to period length with sample rate

}

double TuningMediator::getFundamentalFrequency() const
{
    return 0.0;
}

void TuningMediator::setInput()
{
    // 3) create a fixed period sampler for input
    //    .setDevice and set processingInterval
    //    long enough
}
