#include "func.h"
#include <string.h>
using namespace std;

/* argv[1] - количество строк, argv[2] - период записи */
int main(int argc, char* argv[]) {
    void* shmaddr = NULL;
    int numOfStr, period;
    
    numOfStr = stoi(argv[1]);
    period = stoi(argv[2]);

    if (id_shm == -1) {
        id_shm = req_shm();
    }
    shmaddr = in_shm(id_shm);

    shared* shared_var = (shared*)shmaddr;
    while (1) {
        sleep(period);

        lock(shared_var, FIRST);

        /* Критическая секция */
        if (numOfStr > 0) {
            open_file();
            fputs("Признак первой программы\n", file);
            printf("1\n");
            close_file();
            --numOfStr;
        } else {
            ++(shared_var->stop);
            unlock(shared_var, FIRST);
            break;
        }

        unlock(shared_var, FIRST);
    }

    if (shared_var->stop == 3) {
        close_file();
        und_shm(shmaddr);
        dest_shm(id_shm);
    }

    return EXIT_SUCCESS;
}
