#ifndef SKP_POINT3D_HPP
#define SKP_POINT3D_HPP

#include "common.hpp"

typedef struct {
  PyObject_HEAD
  PyObject* x;
  PyObject* y;
  PyObject* z;
} SkpPoint3d;

static void SkpPoint3d_dealloc(SkpPoint3d* self) {
  Py_DECREF(self->x);
  Py_DECREF(self->y);
  Py_DECREF(self->z);

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpPoint3d_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpPoint3d *self;

  self = (SkpPoint3d*)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->x = PyFloat_FromDouble(0);
    self->y = PyFloat_FromDouble(0);
    self->z = PyFloat_FromDouble(0);
    if (self->x == NULL) { Py_DECREF(self); return NULL; }
    if (self->y == NULL) { Py_DECREF(self); return NULL; }
    if (self->z == NULL) { Py_DECREF(self); return NULL; }
  }

  return (PyObject *)self;
}

static int SkpPoint3d_init(SkpPoint3d *self, PyObject *args, PyObject *kwds) {
  PyObject *x, *y, *z, *tmp;
  if (!PyArg_ParseTuple(args, "OOO", &x, &y, &z)) {
    PyErr_SetString(PyExc_TypeError, "argument error.");
    return -1;
  }

  if (!PyNumber_Check(x) || !PyNumber_Check(y) || !PyNumber_Check(z)) {
    PyErr_SetString(PyExc_TypeError, "xyz must be numeric");
    return -1;
  }

  tmp = self->x;
  Py_INCREF(x);
  self->x = x;
  Py_DECREF(tmp);

  tmp = self->y;
  Py_INCREF(y);
  self->y = y;
  Py_DECREF(tmp);

  tmp = self->z;
  Py_INCREF(z);
  self->z = z;
  Py_DECREF(tmp);

  return 0;
}

static PyObject* SkpPoint3d_getx(SkpPoint3d *self, void *closure) {
  Py_INCREF(self->x);
  return self->x;
}

static PyObject* SkpPoint3d_gety(SkpPoint3d *self, void *closure) {
  Py_INCREF(self->y);
  return self->y;
}

static PyObject* SkpPoint3d_getz(SkpPoint3d *self, void *closure) {
  Py_INCREF(self->z);
  return self->z;
}

static int SkpPoint3d_setx(SkpPoint3d *self, PyObject *value, void *closure) {
  PyObject *tmp;
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "cannot delete");
    return -1;
  }

  if (!PyNumber_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "must be numeric");
    return -1;
  }

  tmp = self->x;
  Py_INCREF(value);
  self->x = value;
  Py_DECREF(tmp);

  return 0;
}

static int SkpPoint3d_sety(SkpPoint3d *self, PyObject *value, void *closure) {
  PyObject *tmp;
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "cannot delete");
    return -1;
  }

  if (!PyNumber_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "must be numeric");
    return -1;
  }

  tmp = self->y;
  Py_INCREF(value);
  self->y = value;
  Py_DECREF(tmp);

  return 0;
}

static int SkpPoint3d_setz(SkpPoint3d *self, PyObject *value, void *closure) {
  PyObject *tmp;
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "cannot delete");
    return -1;
  }

  if (!PyNumber_Check(value)) {
    PyErr_SetString(PyExc_TypeError, "must be numeric");
    return -1;
  }

  tmp = self->z;
  Py_INCREF(value);
  self->z = value;
  Py_DECREF(tmp);

  return 0;
}

static PyGetSetDef SkpPoint3d_getseters[] = {
  {"x", (getter)SkpPoint3d_getx, (setter)SkpPoint3d_setx,
    "x",
    NULL},
  {"y", (getter)SkpPoint3d_gety, (setter)SkpPoint3d_sety,
    "y",
    NULL},
  {"z", (getter)SkpPoint3d_getz, (setter)SkpPoint3d_setz,
    "z",
    NULL},
  {NULL}  /* Sentinel */
};

static PyMemberDef SkpPoint3d_members[] = {
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpPoint3d_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpPoint3dType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Point3d",                                          /* tp_name */
  sizeof(SkpPoint3d),                                     /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpPoint3d_dealloc,                         /* tp_dealloc */
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
  "Model objects",                                        /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpPoint3d_methods,                                     /* tp_methods */
  SkpPoint3d_members,                                     /* tp_members */
  SkpPoint3d_getseters,                                   /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpPoint3d_init,                              /* tp_init */
  0,                                                      /* tp_alloc */
  SkpPoint3d_new,                                         /* tp_new */
};

#endif
