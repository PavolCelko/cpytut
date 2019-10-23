#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

char *getName(char * input)
{
  const char *palko_str = {"palko"};
  char *retval  = malloc(10*sizeof(char));
  char *tempStr = malloc(10*sizeof(char) + 2);
  tempStr[0] = '-';
  tempStr[1] = *input;
  tempStr[2] = '\0';  

  strcpy(retval, palko_str);
  strcat(retval, tempStr);

  free(tempStr);

  return retval;
}

static PyObject * wrapper_getName(PyObject * self, PyObject * args)
{
  char * input;
  char * result = (char*)malloc(10*sizeof(char));;
  PyObject * ret;

  // parse arguments
  if (!PyArg_ParseTuple(args, "s", &input)) {
    return NULL;
  }

  // run the actual function
  result = getName(input);

  // build the resulting string into a Python object.
  ret = PyString_FromString(result);
  free(result);

  return ret;
}

int getValues(float * input)
{
  //malloc(sizeof(float));
  input[0] = 3.14159265f;
  input[1] = 2.71828183f;
  input[2] = 0.00000001f;

  return 3;
}

static PyObject * wrapper_getValues(PyObject * self, PyObject * args)
{
  int len;
  float * result = (float*)malloc(10*sizeof(float));;
  PyObject * ret;

  // parse arguments
  // if (!PyArg_ParseTuple(args, "s", &input)) {
  //   return NULL;
  // }

  // run the actual function
  len = getValues(result);

  // build the resulting string into a Python object.
  ret = PyFloat_FromDouble((double)result[1]);
  
  free(result);

  return ret;
}

static PyMethodDef MathMethods[] = {
 { "getValues", wrapper_getValues, METH_VARARGS, "reveal name" },
 { NULL, NULL, 0, NULL }
};

DL_EXPORT(void) initinfo(void)
{
  Py_InitModule("info", MathMethods);
}

// static PyMethodDef HelloMethods[] = {
//  { "get_name", wrapper_getName, METH_VARARGS, "reveal name" },
//  { NULL, NULL, 0, NULL }
// };

// DL_EXPORT(void) initinfo(void)
// {
//   Py_InitModule("info", HelloMethods);
// }
