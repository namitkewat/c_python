#include <Python.h>
#include "nkmath.h"

static void del_capsule(PyObject *obj){
  Point *p = PyCapsule_GetPointer(obj, "Point");
  if(obj == NULL){
    return ;
  }
  free(p);
}

static Point *to_point(PyObject *obj){
  return (Point *) PyCapsule_GetPointer(obj, "Point");
}

static PyObject *get_capsule(Point *p){
  return PyCapsule_New(p, "Point", &del_capsule);
}

static PyObject *py_point(PyObject *self, PyObject *args){
  Point *p;
  double x, y;
  if (!PyArg_ParseTuple(args, "dd", &x, &y)){
    return NULL;
  };
  p = (Point *)malloc(sizeof(Point));
  p->x = x;
  p->y = y;
  //  return Py_BuildValue("(dd)", p->x, p->y);
  // Above will return value as a tuple of two double;
  // But what if we want to return Pointer?
  // PyCapsule will help
  return get_capsule(p);
};

static PyObject *py_distance(PyObject *self, PyObject *args){
  PyObject *aa, *bb;
  Point *p_aa, *p_bb;
  double result;
  if(!PyArg_ParseTuple(args, "OO", &aa, &bb)){
    return NULL;
  };
  p_aa = to_point(aa);
  p_bb = to_point(bb);
  result = distance(p_aa, p_bb);
  return Py_BuildValue("d", result);
};

static PyMethodDef nkMathMethods[] = {
  {"Point", py_point, METH_VARARGS, "Make a Point"},
  {"Distance", py_distance, METH_VARARGS, "Calculate Distance"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef nkMathModule = {
  PyModuleDef_HEAD_INIT,
  "sample",
  "A Sample Module",
  -1,
  nkMathMethods
};

PyMODINIT_FUNC
PyInit__nkmath(void){
  return PyModule_Create(&nkMathModule);
};
