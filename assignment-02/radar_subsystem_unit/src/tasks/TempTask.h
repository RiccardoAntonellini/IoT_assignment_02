#include "../devices/TempSensor.h"
#include "../kernel/Task.h"
#include "../model/Context.h"

class TempTask : public Task {
    public :
        TempTask(Context* ctx, TempSensor* sensor);
        void tick() override;

    private:
        Context* ctx;
        TempSensor* sensor;
};