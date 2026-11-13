#include "../kernel/Task.h"
#include "../devices/Sonar.h"
#include "../devices/RadarServo.h"
#include "../devices/Potentiometer.h"
#include "../model/context.h"

class ScanTask : public Task {
    public:
        ScanTask (Sonar* sonar, Context* ctx, Potentiometer* pot, RadarServo* servo);
        void tick() override;

    private:
        enum State {STOPPED, SCAN_FORWARD, SCAN_BACKWARD, MANUAL} state;
        Context* ctx;
        Potentiometer* pot;
        Sonar* sonar;
        RadarServo* servo;
        int currentSector = 0;

        void scanStep(); //muove il servo, misura, e aggiorna il context
};