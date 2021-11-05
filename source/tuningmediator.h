#ifndef TUNINGMEDIATOR_H
#define TUNINGMEDIATOR_H

#include <memory>

#include "sampler.h"

class TuningMediator
{
public:
    TuningMediator();
    ~TuningMediator();

    double getFundamentalFrequency() const;
    void setInput(const std::string& name);

private:
    std::unique_ptr<Sampler> sampler;
};

#endif // TUNINGMEDIATOR_H
