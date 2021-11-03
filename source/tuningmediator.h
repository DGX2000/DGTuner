#ifndef TUNINGMEDIATOR_H
#define TUNINGMEDIATOR_H


class TuningMediator
{
public:
    struct FrequencyRange
    {
        double min;
        double max;
    };

public:
    TuningMediator();

    double getFundamentalFrequency() const;
    void setInput();

private:
    // Sampler
};

#endif // TUNINGMEDIATOR_H
