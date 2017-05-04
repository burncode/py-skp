#ifndef SKP_HELPER_MAKE_POINT3D
#define SKP_HELPER_MAKE_POINT3D

#include <SketchUpAPI/geometry.h>

#include "../klass/point3d.hpp"

static PyObject *Skp_Helper_Make_Point3d(SUPoint3D pt) {
  PyObject *x = PyFloat_FromDouble(pt.x);
  PyObject *y = PyFloat_FromDouble(pt.y);
  PyObject *z = PyFloat_FromDouble(pt.z);

  if (x == NULL || y == NULL || z == NULL) return NULL;

  return (PyObject*)PyObject_CallFunction(
      (PyObject*)&SkpPoint3dType,  "OOO", x, y, z);
}

#endif
