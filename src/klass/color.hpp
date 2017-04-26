#ifndef SKP_COLOR_HPP
#define SKP_COLOR_HPP

#include "common.hpp"

#include <SketchUpAPI/color.h>

#define SKP_COLOR_GETTER(el) { \
  return PyLong_FromLong((long)self->el); \
}

#define SKP_COLOR_SETTER(el) { \
  char *msg = "Value must be between 0..255"; \
  if (!PyLong_Check(value)) { \
    PyErr_SetString(PyExc_TypeError, msg); \
    return -1; \
  } \
  \
  SUByte v = (SUByte)PyLong_AsLong(value); \
  if (v < 0 || v > 255) { \
    PyErr_SetString(PyExc_TypeError, msg); \
    return -1; \
  } \
  \
  self->el = v; \
  return 0; \
}

typedef struct {
  PyObject_HEAD
  SUByte red;
  SUByte green;
  SUByte blue;
  SUByte alpha;
} SkpColor;

static void SkpColor_dealloc(SkpColor* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpColor_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = type->tp_alloc(type, 0);

  SkpColor *self = (SkpColor*)py_obj;
  if (self != NULL) {
    self->red = 0;
    self->green = 0;
    self->blue = 0;
    self->alpha = 255;
  }

  return py_obj;
}

static int SkpColor_init(SkpColor *self, PyObject *args, PyObject *kwds) {
  SUByte r,g,b,a;
  if (!PyArg_ParseTuple(args, "bbbb", &r, &g, &b, &a)) {
    PyErr_SetString(PyExc_TypeError, "argument error.");
    return -1;
  }

  self->red   = r;
  self->green = g;
  self->blue  = b;
  self->alpha = a;

  return 0;
}

static PyMemberDef SkpColor_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpColor_getred(SkpColor *self, void *closure) {
  SKP_COLOR_GETTER(red)
}

static PyObject* SkpColor_getgreen(SkpColor *self, void *closure) {
  SKP_COLOR_GETTER(green)
}

static PyObject* SkpColor_getblue(SkpColor *self, void *closure) {
  SKP_COLOR_GETTER(blue)
}

static PyObject* SkpColor_getalpha(SkpColor *self, void *closure) {
  SKP_COLOR_GETTER(alpha)
}

static int SkpColor_setred(SkpColor *self, PyObject *value, void *closure) {
  SKP_COLOR_SETTER(red)
}

static int SkpColor_setgreen(SkpColor *self, PyObject *value, void *closure) {
  SKP_COLOR_SETTER(green)
}

static int SkpColor_setblue(SkpColor *self, PyObject *value, void *closure) {
  SKP_COLOR_SETTER(blue)
}

static int SkpColor_setalpha(SkpColor *self, PyObject *value, void *closure) {
  SKP_COLOR_SETTER(alpha)
}

static PyGetSetDef SkpColor_getseters[] = {
  { "red", (getter)SkpColor_getred, (setter)SkpColor_setred,
    "red", NULL},
  { "green", (getter)SkpColor_getgreen, (setter)SkpColor_setgreen,
    "green", NULL},
  { "blue", (getter)SkpColor_getblue, (setter)SkpColor_setblue,
    "blue", NULL},
  { "alpha", (getter)SkpColor_getalpha, (setter)SkpColor_setalpha,
    "alpha", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpColor_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpColorType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Color",                                            /* tp_name */
  sizeof(SkpColor),                                       /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpColor_dealloc,                           /* tp_dealloc */
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
  "SketchUp Color",                                       /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpColor_methods,                                       /* tp_methods */
  SkpColor_members,                                       /* tp_members */
  SkpColor_getseters,                                     /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpColor_init,                                /* tp_init */
  0,                                                      /* tp_alloc */
  SkpColor_new,                                           /* tp_new */
};

#endif
