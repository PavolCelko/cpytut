#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

#define PI           3.1415926535897932384626433832795
#define EULER_NUM    2.7182818284590452353602874713526

double getPi(void) {  return PI;}

double getEuler(void) {  return EULER_NUM;}

double calcCircArea(double diameter) {  return (getPi() * diameter * diameter / 4);}

int getFloatArray(float * output, const unsigned int len)
{
  unsigned int i;

  for(i = 0; i < len; i++)
    output[i] = 0.001 * i;

  return len;
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

static PyObject * wrapper_getFloatArray(PyObject * self, PyObject * args)
{
  unsigned int len = 0;
  float * pFloatValues;
  PyObject *fList;
  unsigned int input;
  unsigned int i;
  
  //parse arguments
  if (!PyArg_ParseTuple(args, "I", &input)) {
    return NULL;
  }
  len = input;
  fList = PyList_New(len);

  pFloatValues = malloc(input * sizeof(float));

  len = getFloatArray(pFloatValues, len);

  for(i = 0; i < len; i++)
  {
      PyList_SetItem(fList, i, PyFloat_FromDouble(pFloatValues[i]));
  }
  
  return fList;
}

static PyMethodDef MathMethods[] = {
  { "getPi",        wrapper_getPi,         METH_VARARGS, "Returns value of PI number." },
  { "getEuler",     wrapper_getEuler,      METH_VARARGS, "Returns value of EULER number." },
  { "calcCircArea", wrapper_calcCircArea,  METH_VARARGS, "Calculates area of circle based on given diameter." },
  { "getFloats",    wrapper_getFloatArray, METH_VARARGS, "Returns list of float list with data originated from C float array." },
  { NULL, NULL, 0, NULL }
};

DL_EXPORT(void) initinfo(void)
{
  Py_InitModule("info", MathMethods);
}
