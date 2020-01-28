#include "sync.h"
    

int main(int argc, char* argv[]) {
    void* shmaddr = NULL;
    int numOfStr, period, process = 1;
    
    numOfStr = std::stoi(argv[1]);
    period = std::stoi(argv[2]);
    
    printf("Process: %d\nNumber of strings: %d\nPeriod of input: %d\n\n", process, numOfStr, period);

    if (shm_id == -1) { shm_id = shmget(SHARED_KEY, sizeof(shared_data), (IPC_CREAT | 0666)); }
    shmaddr = shmat(shm_id, NULL, 0);
    shared* shared_var = (shared*) shmaddr;
    ++(shared_var->processCount);
    
    while (true) {
        sleep(period);

        lock(shared_var, process);

        if (numOfStr > 0) {
            openFile();
            
            fputs("Program #1\n", file);
            
            closeFile();
            --numOfStr;
        } else {
            --(shared_var->processCount);
            unlock(shared_var);
            break;
        }

        unlock(shared_var);
    }

    if (shared_var->processCount == 0) {
        closeFile();
        shmdt(shmaddr);
        shmctl(shm_id, IPC_RMID, NULL);
    }

    return EXIT_SUCCESS;
}
