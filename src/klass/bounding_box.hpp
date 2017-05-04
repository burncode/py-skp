#ifndef SKP_BOUNDING_BOX_HPP
#define SKP_BOUNDING_BOX_HPP

#include "common.hpp"

#include <SketchUpAPI/geometry.h>

#include "point3d.hpp"

typedef struct {
  PyObject_HEAD
  SUBoundingBox3D bbox;
} SkpBoundingBox;

static void SkpBoundingBox_dealloc(SkpBoundingBox* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpBoundingBox_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = type->tp_alloc(type, 0);

  SkpBoundingBox *self = (SkpBoundingBox*)py_obj;
  if (self != NULL) {
    //self->min_point->x = 0;
  }

  return py_obj;
}

static int SkpBoundingBox_init(SkpBoundingBox *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpBoundingBox_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpBoundingBox_getmin(SkpBoundingBox *self, void *closure) {
  PyObject *py_pt = Skp_Helper_Make_Point3d(self->bbox.min_point);
  if (py_pt == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "cannot get min");
    return NULL;
  }

  return py_pt;
}

static PyObject* SkpBoundingBox_getmax(SkpBoundingBox *self, void *closure) {
  PyObject *py_pt = Skp_Helper_Make_Point3d(self->bbox.max_point);
  if (py_pt == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "cannot get max");
    return NULL;
  }

  return py_pt;
}

static PyGetSetDef SkpBoundingBox_getseters[] = {
  { "min", (getter)SkpBoundingBox_getmin, NULL,
    "min", NULL},
  { "max", (getter)SkpBoundingBox_getmax, NULL,
    "max", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpBoundingBox_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpBoundingBoxType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.SkpBoundingBox",                                   /* tp_name */
  sizeof(SkpBoundingBox),                                 /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpBoundingBox_dealloc,                     /* tp_dealloc */
  0,                                                      /* tp_print */
  0,                                                      /* tp_getattr */
  0,                                                      /* tp_setattr */
  0,                                                      /* tp_reserved */
  0,                                                      /* tp_repr */
  0,                                                      /* tp_as_number */
  0,                                                      /* tp_as_sequence */
  0,                                                      /* tp_as_mapping */
  0,                                                      /* tp_hash  */
  0,                                                      /* tp_call */
  0,                                                      /* tp_str */
  0,                                                      /* tp_getattro */
  0,                                                      /* tp_setattro */
  0,                                                      /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               /*tp_flags */
  "SketchUp SkpBoundingBox",                              /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpBoundingBox_methods,                                 /* tp_methods */
  SkpBoundingBox_members,                                 /* tp_members */
  SkpBoundingBox_getseters,                               /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpBoundingBox_init,                          /* tp_init */
  0,                                                      /* tp_alloc */
  SkpBoundingBox_new,                                     /* tp_new */
};

#endif
