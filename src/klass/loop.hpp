#ifndef SKP_LOOP_HPP
#define SKP_LOOP_HPP

#include "common.hpp"

#include <SketchUpAPI/model/loop.h>

typedef struct {
  PyObject_HEAD
  SULoopRef _su_loop;
} SkpLoop;

static void SkpLoop_dealloc(SkpLoop* self) {
  // TODO: dealloc members

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpLoop_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpLoop *self;

  self = (SkpLoop*)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->_su_loop = SU_INVALID;
  }

  return (PyObject *)self;
}

static int SkpLoop_init(SkpLoop *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpLoop_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpLoop_getentityID(SkpLoop *self, void *closure) {
  GET_ENTITY_BODY(_su_loop, SULoopToEntity)
}

static PyGetSetDef SkpLoop_getseters[] = {
  { "entityID", (getter)SkpLoop_getentityID, NULL,
    "entityID", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpLoop_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpLoopType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Loop",                                             /* tp_name */
  sizeof(SkpLoop),                                        /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpLoop_dealloc,                            /* tp_dealloc */
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
  "SketchUp Loop",                                        /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpLoop_methods,                                        /* tp_methods */
  SkpLoop_members,                                        /* tp_members */
  SkpLoop_getseters,                                      /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpLoop_init,                                 /* tp_init */
  0,                                                      /* tp_alloc */
  SkpLoop_new,                                            /* tp_new */
};

#endif
