#ifndef SKP_LOOP_HPP
#define SKP_LOOP_HPP

#include "common.hpp"

#include <SketchUpAPI/model/loop.h>

typedef struct {
  SkpDrawingElement skp_drawing_element;
  SULoopRef _su_loop;
} SkpLoop;

static void SkpLoop_dealloc(SkpLoop* self) {
  // TODO: dealloc members

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpLoop__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity))
    ent_self->_su_entity = SULoopToEntity(((SkpLoop*)self)->_su_loop);

  return ent_self->_su_entity;
}

static PyObject * SkpLoop_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpDrawingElementType.tp_new(type, args, kwds);

  SkpLoop *self = (SkpLoop*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpLoop__get_su_entity;

    self->_su_loop = SU_INVALID;
  }

  return py_obj;
}

static int SkpLoop_init(SkpLoop *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpLoop_members[] = {
  {NULL}  /* Sentinel */
};

static PyGetSetDef SkpLoop_getseters[] = {
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
