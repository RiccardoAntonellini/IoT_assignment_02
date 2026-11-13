#include "../kernel/Task.h"
#include "../model/Context.h"
#include "../devices/Led.h"

class SystemTask : public Task {
    public:
        SystemTask(Context* ctx, Led* greenLed);
        void tick() override;

    private:
        Context* ctx;
        Led* greenLed;
};