#pragma once

#include <Arduino.h>
#include "Task.h"
#include "config.h"

class Scheduler {
    public:
        Scheduler();
        ~Scheduler();
        void init(int basePeriod);
        void addTask(Task* task);
        void schedule();
        void resync();

    private:
        struct Node {
            Task* task;
            Node* next;
        };

        int basePeriod;
        Node* head;
        Node* tail;
        unsigned long nextTick;
};