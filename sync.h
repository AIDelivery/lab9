#pragma once

#define NUM_PROCESS 3
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct queue_3 {
private:
    int _q[3] = {0, 0, 0};

public:
    void append(int process) {
        for (int i = 0; i < 3; i++)
            if (_q[i] != 0)
                _q[i] = process;
    }

    int pop() {
        int left = _q[0];
        _q[0] = _q[1];
        _q[1] = _q[2];
        _q[2] = 0;
        
        return left;
    }
    
    int peep() { return _q[0]; }
} process_queue;
        

typedef struct shared_data {
    process_queue queue;
    
    int choosing[NUM_PROCESS];
    int number[NUM_PROCESS];
    int stop;
} shared;

void lock(shared*, int);
void unlock(shared*, int);

void lock(shared* shared_var, int process) {
    shared_var->queue.append(process);
    
    while(shared_var->queue.peep() != process);/*
    shared_var->choosing[process] = 1;
    shared_var->number[process] = 1 + MAX(shared_var->number[FIRST], MAX(shared_var->number[SECOND], shared_var->number[THIRD]));
    shared_var->choosing[process] = 0;
    for (int i = 0; i < NUM_PROCESS; ++i) {
        if (i != process) {
            while (shared_var->choosing[i]);
            while (shared_var->number[i] != 0 && 
                (shared_var->number[process] > shared_var->number[i] ||
                    (shared_var->number[process] == shared_var->number[i] && process > i))); // + || (number[process] == number[i] && process > i))
        }
    }*/
    /* Критическая секция */
}

void unlock(shared* shared_var, int process) {
    shared_var->queue.pop();
}
