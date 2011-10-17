#ifndef SPAMMODULE_H

    #define SPAMMODULE_H
    #include <Python.h> //it should be included before everything and already includes standard libraries

    class Serial{
        public:
            //constructor
            Serial(){};

            //destructor
            ~Serial(){};

            //public methods
            bool load_python_interpreter();
            bool import_python_module();
            bool unload_python_interpreter();
            int send_4_bytes(char *byte_array);
            int receive_4_bytes(char *byte_array);

            //functions to create link between references and python functions
            bool load_py_function_send();
            bool load_py_function_receive();

        private:
            //references to python
            PyObject *py_module_serial;
            PyObject *py_function_send;
            PyObject *py_function_send_args;
            PyObject *py_function_receive;
            PyObject *py_function_receive_args;


            //functions to destroy link between references and python functions
            bool unload_py_function_send();
            bool unload_py_function_receive();
    };

#endif
