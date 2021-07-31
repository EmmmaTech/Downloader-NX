#pragma once

class ProgressEvent
{
    ProgressEvent() = default;

    int current = 0;
    int max = 60;

    public:

    ProgressEvent(const ProgressEvent&) = delete;
    ProgressEvent& operator=(const ProgressEvent &) = delete;
    ProgressEvent(ProgressEvent &&) = delete;
    ProgressEvent & operator=(ProgressEvent &&) = delete;

    static ProgressEvent& getInstance()
    {
        static ProgressEvent pe;
        return pe;
    }

    void reset()
    {
        current = 0;
        max = 60;
    }

    inline void setTotalSteps(int steps) {max = steps;}
    inline void setStep(int step) {current = step;}
    inline void incrementStep(int increment) {current += increment;}
    inline int getMax() {return max;}
    inline int getStep() {return current;}
    inline bool finished() {return current == max;}
};