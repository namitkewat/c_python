#include <Python.h>
#include "chi2.h"

/* Docstrings */
static char module_docstring[] =
    " This module provides an interface for calculating chi-squared using C.\n\
    Example Usage:                \n\
      In [7]: import _chi         \n\
                                  \n\
      In [8]: import numpy as np  \n\
                                  \n\
      In [9]: _chi.chi2(2.0, 1.0, np.array([-1.0, 4.2, 30.6]),  np.array([-1.5, 8.0, 63.0]), np.array([1.0, 1.5, 0.6]))\n\
      Out[9]: 2.8988888888888766  \n";

static char chi2_docstring[] =
    "Calculate the chi-squared of some data given a model.";


static PyObject *chi2_chi2(PyObject *self, PyObject *args){
  double m, b, value;
  PyObject *x_bufobj, *y_bufobj, *yerr_bufobj, *ret;
  Py_buffer x_view, y_view, yerr_view;

  /* Parse the supplied Python object */
  if (!PyArg_ParseTuple(args, "ddOOO", &m, &b, &x_bufobj, &y_bufobj, &yerr_bufobj)){ return NULL;};

  /* Extract buffer info */
  if (PyObject_GetBuffer(x_bufobj, &x_view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1){ return NULL;};
  if (PyObject_GetBuffer(y_bufobj, &y_view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1){ return NULL;};
  if (PyObject_GetBuffer(yerr_bufobj, &yerr_view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1){ return NULL;};

  if (x_view.ndim != 1 || y_view.ndim != 1 || yerr_view.ndim != 1) {
    PyErr_SetString(PyExc_TypeError, "Expected a 1-dimensional array");
    goto fail;
  }

  /* Check the type of items in the array */
  if (strcmp(x_view.format,"d") != 0 || strcmp(y_view.format,"d") != 0 || strcmp(yerr_view.format,"d") != 0) {
    PyErr_SetString(PyExc_TypeError, "Expected an array of doubles");
    goto fail;
  }
  /* Pass the raw buffer along with other arguments to the C function */
  value = chi2(m, b, x_view.buf, y_view.buf, yerr_view.buf, x_view.shape[0]);

  /* Now we are done; we can now release the Buffers */
  PyBuffer_Release(&x_view);
  PyBuffer_Release(&y_view);
  PyBuffer_Release(&yerr_view);

  if (value < 0.0) {
    PyErr_SetString(PyExc_RuntimeError, "Chi-squared returned an impossible value.");
    return NULL;
  }


  /* Builing the Output */
  ret = Py_BuildValue("d", value);
  return ret;

  fail:
    PyBuffer_Release(&x_view);
    PyBuffer_Release(&y_view);
    PyBuffer_Release(&yerr_view);
    return NULL;
}

/* Module specification */
static PyMethodDef module_methods[] = {
    {"chi2", chi2_chi2, METH_VARARGS, chi2_docstring},
    {NULL, NULL, 0, NULL}
};


/* Module structure */
static struct PyModuleDef chimodule = {
  PyModuleDef_HEAD_INIT,
  "_chi",           /* name of module */
  module_docstring,  /* Doc string (may be NULL) */
  -1,                 /* Size of per-interpreter state or -1 */
  module_methods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit__chi(void) {
  return PyModule_Create(&chimodule);
}
