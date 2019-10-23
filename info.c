#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

#define PI           3.1415926535897932384626433832795
#define EULER_NUM    2.7182818284590452353602874713526

double getPi(void) {  return PI;}

double getEuler(void) {  return EULER_NUM;}

double calcCircArea(double diameter) {  return getPi() * diameter / 4;}

int getFloatList(float * input)
{
  //malloc(sizeof(float));
  input[0] = 3.14159265f;
  input[1] = 2.71828183f;
  input[2] = 0.00000001f;

  return 3;
}

static PyObject * wrapper_getPi(PyObject * self, PyObject * args)
{
  PyObject * ret;

  // build the resulting string into a Python object.
  ret = PyFloat_FromDouble(getPi());
  
  return ret;
}

static PyObject * wrapper_getEuler(PyObject * self, PyObject * args)
{
  double c_RetVal;
  PyObject * ret;

  // run the actual function
  c_RetVal = getEuler();
  // build the resulting string into a Python object.
  ret = PyFloat_FromDouble(c_RetVal);
    
  return ret;
}

static PyObject * wrapper_calcCircArea(PyObject * self, PyObject * args)
{
  double c_RetVal;
  PyObject * ret;
  double input;

  //parse arguments
  if (!PyArg_ParseTuple(args, "d", &input)) {
    return NULL;
  }

  // run the actual function
  c_RetVal = calcCircArea(input);

  // build the resulting string into a Python object.
  ret = PyFloat_FromDouble(c_RetVal);

  return ret;
}

static PyMethodDef MathMethods[] = {
  { "getPi",        wrapper_getPi,        METH_VARARGS, "Returns value of PI number." },
  { "getEuler",     wrapper_getEuler,     METH_VARARGS, "Returns value of EULER number." },
  { "calcCircArea", wrapper_calcCircArea, METH_VARARGS, "Calculates area of circle based on given diameter." },
  { NULL, NULL, 0, NULL }
};

DL_EXPORT(void) initinfo(void)
{
  Py_InitModule("info", MathMethods);
}
