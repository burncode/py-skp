#ifndef SKP_CURVE_HPP
#define SKP_CURVE_HPP

#include "common.hpp"

#include <SketchUpAPI/model/curve.h>

typedef struct {
  PyObject_HEAD
  SUCurveRef _su_curve;
} SkpCurve;

static void SkpCurve_dealloc(SkpCurve* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpCurve_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = type->tp_alloc(type, 0);

  SkpCurve *self = (SkpCurve*)py_obj;
  if (self != NULL) {
    self->_su_curve = SU_INVALID;
  }

  return py_obj;
}

static int SkpCurve_init(SkpCurve *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpCurve_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpCurve_getedges(SkpCurve *self, void *closure);

static PyGetSetDef SkpCurve_getseters[] = {
  { "edges", (getter)SkpCurve_getedges, NULL,
    "edges", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpCurve_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpCurveType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Curve",                                            /* tp_name */
  sizeof(SkpCurve),                                       /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpCurve_dealloc,                           /* tp_dealloc */
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               /* tp_flags */
  "SketchUp Curve",                                       /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpCurve_methods,                                       /* tp_methods */
  SkpCurve_members,                                       /* tp_members */
  SkpCurve_getseters,                                     /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpCurve_init,                                /* tp_init */
  0,                                                      /* tp_alloc */
  SkpCurve_new,                                           /* tp_new */
};

#endif
