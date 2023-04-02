#include "SearchTime.h"

SearchTime::SearchTime(time_t initialTime, time_t finalTime) {
    this->initialTime = initialTime;
    this->finalTime = finalTime;
}

time_t SearchTime::getInitialTime() const {
    return initialTime;
}

time_t SearchTime::getFinalTime() const {
    return finalTime;
}

time_t SearchTime::duration() {
    return duration(initialTime, finalTime);
}

time_t SearchTime::duration(time_t initialTime, time_t finalTime) {
    return finalTime - initialTime;
}
