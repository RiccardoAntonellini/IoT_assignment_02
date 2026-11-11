#pragma once

class Task
{
private:
    int myPeriod;
    int timeElapsed;
    bool active;
public:
    Task(int period): myPeriod(period), timeElapsed(0), active(true) {};
    virtual void tick() = 0; //ciò che deve fare veramente la task

    bool updateAndCheckTime(int basePeriod) {
        timeElapsed += basePeriod;
        if(timeElapsed >= myPeriod) {
            timeElapsed = 0;
            return true;
        }
        else {
            return false;
        }
    }
    void setPeriod(int period) {
        myPeriod = period;
    }
    int getPeriod() {
        return myPeriod;
    }
    void setActive(bool isActive) {
        active = isActive;
        timeElapsed = 0;
    }
    bool isActive() {
        return active;
    }
    virtual ~Task() {};
};
