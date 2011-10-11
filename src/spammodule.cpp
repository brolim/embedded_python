#include "spammodule.h"

static PyObject* spam_system(PyObject *self, PyObject *args) {

	//parse args pointer and transform it into c values using PyArg_ParseTuple function
    const char *command;
    if (!PyArg_ParseTuple(args, "s", &command)) return NULL;
    
    //'c system() call and return its returning value to python module'
    return Py_BuildValue("i", system(command));
}
