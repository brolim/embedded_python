#include "spammodule.h"

int main(){
    printf("running... \n\n\n");
    
    //initialize python interpreter
    Py_Initialize();
    
    //python path. If you are using linux, you can find this inside the python interpreter using this command:
    // >>> import sys
    // >>> ':'.join(sys.path)[1:]
    char *python_path = "/usr/lib/python2.7:/usr/lib/python2.7/plat-linux2:/usr/lib/python2.7/lib-tk:/usr/lib/python2.7/lib-old:/usr/lib/python2.7/lib-dynload:/usr/local/lib/python2.7/dist-packages:/usr/lib/python2.7/dist-packages:/usr/lib/python2.7/dist-packages/PIL:/usr/lib/pymodules/python2.7/gtk-2.0:/usr/lib/python2.7/dist-packages/gst-0.10:/usr/lib/python2.7/dist-packages/gtk-2.0:/usr/lib/pymodules/python2.7:/usr/lib/pymodules/python2.7/ubuntuone-client:/usr/lib/pymodules/python2.7/ubuntuone-control-panel:/usr/lib/pymodules/python2.7/ubuntuone-storage-protocol";
    
    //setting our module's path to the python path
    char *module_path = ":../py_serial_connection";
    char *new_path = (char*)calloc(strlen(module_path)+strlen(python_path)+ 2, 1); 
    strcpy(new_path, python_path); 
    strcat(new_path, module_path);
    PySys_SetPath(new_path); 

    //convert C string to Python string
    PyObject *python_string = PyString_FromString("serial_connection");
    
    //importing our module 
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
    printf("Result of call: %s\n", PyString_AsString(python_returning_value));
    
    //frees python variables on python interpreter
    Py_DECREF(python_returning_value);
    Py_XDECREF(python_function);
    Py_DECREF(python_module);

    //finalize python interpreter
    Py_Finalize();
    
    printf("\n\ndone\n");
    return 0;
}




