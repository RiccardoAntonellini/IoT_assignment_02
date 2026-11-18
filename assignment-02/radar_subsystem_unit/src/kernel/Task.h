#pragma once

class Task
{
    public:
        Task(int period): myPeriod(period), timeElapsed(0), active(true) {};
        // ogni task deve avere questo metodo ma lo scrive chi eredita da task
        virtual void tick() = 0;

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

    private:
        int myPeriod;
        int timeElapsed;
        bool active;
};
