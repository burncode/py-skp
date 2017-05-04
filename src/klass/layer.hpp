#ifndef SKP_LAYER_HPP
#define SKP_LAYER_HPP

#include "common.hpp"

#include <SketchUpAPI/model/layer.h>

#include "entity.hpp"

typedef struct {
  SkpEntity skp_entilty;
  SULayerRef _su_layer;
} SkpLayer;

static void SkpLayer_dealloc(SkpLayer* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpLayer__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity)) {
    ent_self->_su_entity = SULayerToEntity(((SkpLayer*)self)->_su_layer);
  }

  return ent_self->_su_entity;
}

static PyObject * SkpLayer_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpEntityType.tp_new(type, args, kwds);

  SkpLayer *self = (SkpLayer*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpLayer__get_su_entity;

    self->_su_layer = SU_INVALID;
  }

  return py_obj;
}

static int SkpLayer_init(SkpLayer *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpLayer_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpLayer_getname(SkpLayer *self, void *closure) {
  SKP_GET_STRING_BODY(SULayerGetName, _su_layer, "cannot get name")
}

static int SkpLayer_setname(SkpLayer *self, PyObject *value, void *closure) {
  //TODO: Cannot overwrite Layer0
  SKP_SET_STRING_BODY(SULayerSetName, _su_layer, "cannot set name")
}

static PyGetSetDef SkpLayer_getseters[] = {
  { "name", (getter)SkpLayer_getname, (setter)SkpLayer_setname,
    "name", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpLayer_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpLayerType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Layer",                                            /* tp_name */
  sizeof(SkpLayer),                                       /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpLayer_dealloc,                           /* tp_dealloc */
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
  "SketchUp Layer",                                       /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpLayer_methods,                                       /* tp_methods */
  SkpLayer_members,                                       /* tp_members */
  SkpLayer_getseters,                                     /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpLayer_init,                                /* tp_init */
  0,                                                      /* tp_alloc */
  SkpLayer_new,                                           /* tp_new */
};

#endif
