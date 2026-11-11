#pragma once

#include <Arduino.h>
#include "Task.h"
#include "config.h"

class Scheduler {
    public:
        // costruttore e distruttore
        Scheduler();
        ~Scheduler();

        void init(int basePeriod);
        void addTask(Task* task);
        void schedule();
        void resync();

    private:
        // nodo della lista di task con singolo puntatore al task e al prossimo nodo
        struct Node {
            Task* task;
            Node* next;
        };

        int basePeriod;
        Node* head;
        Node* tail; // ne teniamo traccia per aggiungere nuovi task in coda
        unsigned long nextTick; // istante in cui deve avvenire il prossimo tick
};