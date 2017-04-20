#ifndef SKP_ENTITY_HPP
#define SKP_ENTITY_HPP

#include "common.hpp"

#include <SketchUpAPI/model/entity.h>

typedef struct {
  PyObject_HEAD
  SUEntityRef _su_entity;
  SUEntityRef (*get_su_entity)(void*);
} SkpEntity;

static void SkpEntity_dealloc(SkpEntity* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpEntity_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = type->tp_alloc(type, 0);

  SkpEntity *self = (SkpEntity*)py_obj;
  if (self != NULL) {
    self->_su_entity = SU_INVALID;
  }

  return py_obj;
}

static int SkpEntity_init(SkpEntity *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpEntity_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpEntity_getentityID(SkpEntity *self, void *closure) {
  int32_t entity_id = 0;
  SUResult res = SUEntityGetID(self->get_su_entity(self), &entity_id);
  if (checkerror(res, "Cannot get entityID")) return NULL;

  return PyLong_FromLong((long)entity_id);
}

static PyGetSetDef SkpEntity_getseters[] = {
  { "entityID", (getter)SkpEntity_getentityID, NULL,
    "entityID", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpEntity_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpEntityType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Entity",                                           /* tp_name */
  sizeof(SkpEntity),                                      /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpEntity_dealloc,                          /* tp_dealloc */
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
  "SketchUp Entity",                                      /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpEntity_methods,                                      /* tp_methods */
  SkpEntity_members,                                      /* tp_members */
  SkpEntity_getseters,                                    /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpEntity_init,                               /* tp_init */
  0,                                                      /* tp_alloc */
  SkpEntity_new,                                          /* tp_new */
};

#endif
