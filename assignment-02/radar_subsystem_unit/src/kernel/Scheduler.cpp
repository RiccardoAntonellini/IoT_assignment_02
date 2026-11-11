#include "Scheduler.h"

// costruttore con tutti i valori default
Scheduler::Scheduler() : head(nullptr), tail(nullptr), nextTick(0) {}

// distruttore --> elimino un nodo alla volta dalla testa in avanti
Scheduler::~Scheduler() {
    Node *n = head;
    while (n != nullptr) {
        Node *next = n->next;
        delete n;
        n = next;
    }
}

// imposta periodo base e il prossimo tick tra baseperiod ms
void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    nextTick = millis() + basePeriod;
}

// metodo per aggiunta di un task
bool Scheduler::addTask(Task *task) {

    //il task non deve mancare sennò fallisce schedule()
    if (task == nullptr) {
        return false;
    }

    Node *n = new Node;
    if (n == nullptr) {
        return false;
    }
    n->task = task;
    n->next = nullptr;

    if (tail == nullptr) {
        head = n;
    } else {
        tail->next = n;
    }
    tail = n; //in ogni caso si aggiorna la coda

    return true;
}

// serve per riallineare il prossimo tick dato che dopo il deep sleep millis() è rimasto indietro
void Scheduler::resync() {
    nextTick = millis() + basePeriod;
}

// ad ogni tick viene effettuato un giro dello scheduler
void Scheduler::schedule() {

    // ciclo di busy waiting per attendere il prossimo tick
    while ((long) (millis() - nextTick) < 0) {

    }

    nextTick += basePeriod;

    // scorrimento della lista da inizio a fine
    for (Node *n = head; n != nullptr; n = n->next) {
        Task *t = n->task;

        // se il task è attivo accumula basePeriod e dice se il suo periodo è scaduto
        // successivamente si avanza di un passo
        if (t->isActive() && t->updateAndCheckTime(basePeriod)) {
            t->tick();
        }
    }
}