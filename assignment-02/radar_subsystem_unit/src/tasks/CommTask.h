#include "../kernel/Task.h"
#include "../model/Context.h"

class CommTask : public Task {
    public:
        CommTask(Context* ctx);
        void tick() override;

    private:
        Context* ctx;
        SystemState lastState; //ultimo stato inviato
        int lastSector; //ultimo settore inviato
        bool firstSend; //per inviare 
        const char* stateToString(SystemState s);
};