#pragma once

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <string.h>

#define SHARED_KEY 1001

FILE* file = NULL;
int shm_id = -1;

typedef struct queue_3 {
private:
    int _q[3] = {0, 0, 0};

public:
    bool is_full() {
        for (int i = 0; i < 3; i++)
            if (_q[0] == 0) return false;

        return true;
    }

    void append(int process) {
        int i;

        // printf("Before appending: %d %d %d\n", _q[0], _q[1], _q[2]);

        for (i = 0; i < 3; i++)
            if (_q[i] == 0) {
                _q[i] = process;
                break;
            }


        // printf("After appending: %d %d %d\n", _q[0], _q[1], _q[2]);

        // printf("I: %d\n", i);
    }

    int pop() {
        // printf("Before popping: %d %d %d\n", _q[0], _q[1], _q[2]);
        int left = _q[0];
        _q[0] = _q[1];
        _q[1] = _q[2];
        _q[2] = 0;

        // printf("After popping: %d %d %d\n", _q[0], _q[1], _q[2]);

        return left;
    }

    int peep(int _i = 0) { return _q[_i]; }
} process_queue;


typedef struct shared_data {
    process_queue accessQueue;
    int processCount;
    int terminatedProcesses;
} shared;



void openFile() {
    if (shm_id == -1)
        file = fopen("text.txt", "w");
    else
        file = fopen("text.txt", "a");
}

void closeFile() {
    fclose(file);
}

void lock(shared* shared_var, int process) {
    shared_var->accessQueue.append(process);
    // printf("Queue: %d %d %d\n", shared_var->accessQueue.peep(0), shared_var->accessQueue.peep(1), shared_var->accessQueue.peep(2));
    while(shared_var->accessQueue.peep() != process);
}

void unlock(shared* shared_var) {
    shared_var->accessQueue.pop();
}
