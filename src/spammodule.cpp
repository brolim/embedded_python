#include "spammodule.h"

int main(){
    printf("running... \n\n\n");
    
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    //initialize python interpreter
    Py_Initialize();
    
    //setting our module's path to the python path
    char *path, *newpath;
    char *add_to_path = ":/home/brolim/projetos/karmonitor/embedded_python/py_serial_connection";
    path = Py_GetPath();
    newpath = (char*)calloc(strlen(path)+strlen(add_to_path)+ 2, 1); 
    strcpy(newpath, path); 
    strcat(newpath, add_to_path);
    PySys_SetPath(newpath); 

    //import our module    
    pName = PyString_FromString("serial_connection");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    //module import validation
    if(pModule == NULL){
        PyErr_Print();
        fprintf(stderr, "Failed to load module...\n");
        return 1;
    }

    //get reference to the python function (method)
    pFunc = PyObject_GetAttrString(pModule, "add");
    
    //function reference validation
    if(!pFunc || !PyCallable_Check(pFunc)){
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function 'add' in python module\n");
    }
    
    //set number of arguments of our function
    pArgs = PyTuple_New(2);
    
    //c arguments will be converted to python arguments with this loop
    for (int i=0; i<2; i++) {
    
        //argument conversion from C type to Python type
        pValue = PyInt_FromLong(2);
        
        //argument conversion validation
        if (!pValue) {
            Py_DECREF(pArgs);
            Py_DECREF(pModule);
            fprintf(stderr, "Cannot convert argument\n");
            return 1;
        }
        
        //add python argument to arguments list
        PyTuple_SetItem(pArgs, i, pValue);
    }
    
    //call python function
    pValue = PyObject_CallObject(pFunc, pArgs);
    
    Py_DECREF(pArgs);
    
    //call validation
    if (pValue == NULL) {
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return 1;
    }
    
    //print python value
    printf("Result of call: %ld\n", PyInt_AsLong(pValue));
    
    Py_DECREF(pValue);
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    //finalize python interpreter
    Py_Finalize();
    
    printf("\n\ndone\n");
    return 0;
}




