#include "spammodule.h"

bool Serial::load_python_interpreter(){
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

    return true;
}

bool Serial::import_python_module(){
    //convert C string to Python string
    PyObject *python_string = PyString_FromString("serial_connection");
    
    //importing our module 
    this->py_module_serial = PyImport_Import(python_string);
    
    //frees python_string on python interpreter
    Py_DECREF(python_string);

    //module import validation
    if(this->py_module_serial == NULL){
        PyErr_Print();
        fprintf(stderr, "Failed to load module...\n");
        return false;
    }
    
    return true;
}

bool Serial::load_py_function_receive(){

    //get reference to the python function
    this->py_function_receive = PyObject_GetAttrString(this->py_module_serial, "add");
    
    //function reference validation
    if(!this->py_function_receive || !PyCallable_Check(py_function_receive)){
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Cannot find function 'add' in python module\n");
        return false;
    }
    
    //set number of arguments of our function
    this->py_function_receive_args = PyTuple_New(2);
    
    //c arguments will be converted to python arguments with this loop
    PyObject *python_argument;
    for (int i=0; i<2; i++) {
    
        //argument conversion from C type to Python type
        python_argument = PyInt_FromLong(2);
        
        //argument conversion validation
        if (!python_argument) {
            Py_DECREF(this->py_function_receive_args);
            Py_DECREF(this->py_module_serial);
            fprintf(stderr, "Cannot convert argument\n");
            return false;
        }
        
        //add python argument to arguments list
        PyTuple_SetItem(this->py_function_receive_args, i, python_argument);
    }
    
    //frees python_argument on python interpreter
    Py_DECREF(python_argument);
    
    return true;
}

int Serial::receive_4_bytes(char *byte_array){
    
    //call python function
    PyObject *py_returning_value = PyObject_CallObject(this->py_function_receive, this->py_function_receive_args);
    
    //frees python_function_arguments on python interpreter
    Py_DECREF(this->py_function_receive_args);
    
    //call validation
    if (py_returning_value == NULL) {
        Py_DECREF(this->py_function_receive);
        Py_DECREF(this->py_module_serial);
        PyErr_Print();
        fprintf(stderr,"Call failed\n");
        return 1;
    }
    
    //print python value
    printf("Result of call: %s\n", PyString_AsString(py_returning_value));
    
    Py_DECREF(py_returning_value);
    return 0;
}

bool Serial::unload_python_interpreter(){

    //frees python variables on python interpreter
    Py_XDECREF(this->py_function_receive);
    Py_DECREF(this->py_module_serial);

    //finalize python interpreter
    Py_Finalize();
    
    return true;
}

int main(){
    printf("running... \n\n\n");
    
    Serial serial = Serial();

    if(not serial.load_python_interpreter()) return 1;
    if(not serial.import_python_module()) return 1;
    if(not serial.load_py_function_receive()) return 1;
    char *hi;
    serial.receive_4_bytes(hi);
    
    serial.unload_python_interpreter();
    
    printf("\n\ndone\n");
    return 0;
}




