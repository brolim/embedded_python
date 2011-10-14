#include "spammodule.h"

int main(){
    printf("running... \n\n\n");
    
    //initialize python interpreter
    Py_Initialize();
    
    //open python script
    FILE * python_script = fopen("../python/serial_connection.py", "r");
    
    //run the open python script
    PyRun_SimpleFile(python_script, "../python/serial_connection.py");
    
    //finalize python interpreter
    Py_Finalize();
    
    printf("\n\ndone\n");
    return 0;
}
