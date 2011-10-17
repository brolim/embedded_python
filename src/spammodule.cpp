#include "spammodule.h"

int main(){
    printf("running... \n\n\n");
    
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

    //convert C string to Python string
    PyObject *python_string = PyString_FromString("serial_connection");
    
    //import module 
    PyObject *python_module = PyImport_Import(python_string);
    
    //frees python_string on python interpreter
    Py_DECREF(python_string);

    //module import validation
    if(python_module == NULL){
        PyErr_Print();
        fprintf(stderr, "Failed to load module...\n");
        return 1;
    }

    //get reference to the python function
    PyObject *python_function = PyObject_GetAttrString(python_module, "add");
    
    //function reference validation
    if(!python_function || !PyCallable_Check(python_function)){
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function 'add' in python module\n");
    }
    
    //set number of arguments of our function
    PyObject *python_function_arguments = PyTuple_New(2);
    
    //c arguments will be converted to python arguments with this loop
    PyObject *python_argument;
    for (int i=0; i<2; i++) {
    
        //argument conversion from C type to Python type
        python_argument = PyInt_FromLong(2);
        
        //argument conversion validation
        if (!python_argument) {
            Py_DECREF(python_function_arguments);
            Py_DECREF(python_module);
            fprintf(stderr, "Cannot convert argument\n");
            return 1;
        }
        
        //add python argument to arguments list
        PyTuple_SetItem(python_function_arguments, i, python_argument);
    }
    
    //frees python_argument on python interpreter
    Py_DECREF(python_argument);

    //call python function
    PyObject *python_returning_value = PyObject_CallObject(python_function, python_function_arguments);
    
    //frees python_function_arguments on python interpreter
    Py_DECREF(python_function_arguments);
    
    //call validation
    if (python_returning_value == NULL) {
        Py_DECREF(python_function);
        Py_DECREF(python_module);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return 1;
    }
    
    //print python value
    printf("Result of call: %ld\n", PyInt_AsLong(python_returning_value));
    
    //frees python variables on python interpreter
    Py_DECREF(python_returning_value);
    Py_XDECREF(python_function);
    Py_DECREF(python_module);

    //finalize python interpreter
    Py_Finalize();
    
    printf("\n\ndone\n");
    return 0;
}




