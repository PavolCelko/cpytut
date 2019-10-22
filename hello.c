#include <stdio.h>
#include <Python.h>

char *hello(void)
{
    char *x = "palko";

    return x;
}

static PyObject * hello_wrapper(PyObject * self, PyObject * args)
{
  char * input;
//   char * result;
  char * result;
  PyObject * ret;

  // parse arguments
  if (!PyArg_ParseTuple(args, "s", &input)) {
    return NULL;
  }

  // run the actual function
//   result = hello(input);
  result = (char*)malloc(10*sizeof(char));
  result[0] = 'x';
  result[1] = 'a';
  result[2] = 'l';
  result[3] = 'k';
  result[4] = 'o';
  result[5] = '\0';

  // build the resulting string into a Python object.
  ret = PyString_FromString(result);
  free(result);

  return ret;
}

static PyMethodDef HelloMethods[] = {
 { "hello", hello_wrapper, METH_VARARGS, "Say hello" },
 { NULL, NULL, 0, NULL }
};

DL_EXPORT(void) inithello(void)
{
  Py_InitModule("hello", HelloMethods);
}

// void main()
// {
//     printf("Hello, World C lang\n");

// }