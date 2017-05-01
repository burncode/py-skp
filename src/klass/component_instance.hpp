#ifndef SKP_COMPONENT_INSTANCE_HPP
#define SKP_COMPONENT_INSTANCE_HPP

#include "common.hpp"

#include <SketchUpAPI/model/component_instance.h>

#include "drawing_element.hpp"

typedef struct {
  SkpDrawingElement skp_drawing_element;
  SUComponentInstanceRef _su_ins;
} SkpComponentInstance;

static void SkpComponentInstance_dealloc(SkpComponentInstance* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpComponentInstance__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity))
    ent_self->_su_entity = SUComponentInstanceToEntity(((SkpComponentInstance*)self)->_su_ins);

  return ent_self->_su_entity;
}

static PyObject * SkpComponentInstance_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpDrawingElementType.tp_new(type, args, kwds);

  SkpComponentInstance *self = (SkpComponentInstance*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpComponentInstance__get_su_entity;

    self->_su_ins = SU_INVALID;
  }

  return py_obj;
}

static int SkpComponentInstance_init(SkpComponentInstance *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpComponentInstance_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpComponentInstance_getname(SkpComponentInstance *self, void *closure) {
  SKP_GET_STRING_BODY(SUComponentInstanceGetName, _su_ins, "cannot get name")
}

static int SkpComponentInstance_setname(SkpComponentInstance *self, PyObject *value, void *closure) {
  SKP_SET_STRING_BODY(SUComponentInstanceSetName, _su_ins, "cannot set name")
}

static PyObject* SkpComponentInstance_getguid(SkpComponentInstance *self, void *closure) {
  SKP_GET_STRING_BODY(SUComponentInstanceGetGuid, _su_ins, "cannot get guid")
}

static int SkpComponentInstance_setguid(SkpComponentInstance *self, PyObject *value, void *closure) {
  SKP_SET_STRING_BODY(SUComponentInstanceSetGuid, _su_ins, "cannot set guid")
}

static PyObject* SkpComponentInstance_getattached_instances(SkpComponentInstance *self, void *closure);

static PyObject* SkpComponentInstance_getlocked(SkpComponentInstance *self, void *closure) {
  SKP_GET_BOOL_BODY(SUComponentInstanceIsLocked, _su_ins, "connot get locked")
}

static int SkpComponentInstance_setlocked(SkpComponentInstance *self, PyObject *value, void *closure) {
  SKP_SET_BOOL_BODY(SUComponentInstanceSetLocked, _su_ins, "cannot set locked")
}

static PyGetSetDef SkpComponentInstance_getseters[] = {
  { "name", (getter)SkpComponentInstance_getname, (setter)SkpComponentInstance_setname,
    "name", NULL},
  { "guid", (getter)SkpComponentInstance_getguid, (setter)SkpComponentInstance_setguid,
    "guid", NULL},
  { "attached_instances", (getter)SkpComponentInstance_getattached_instances, NULL,
    "attached_instances", NULL},
  { "locked", (getter)SkpComponentInstance_getlocked, (setter)SkpComponentInstance_setlocked,
    "locked", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpComponentInstance_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpComponentInstanceType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.ComponentInstance",                                /* tp_name */
  sizeof(SkpComponentInstance),                           /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpComponentInstance_dealloc,               /* tp_dealloc */
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
  "SketchUp ComponentInstance",                           /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpComponentInstance_methods,                           /* tp_methods */
  SkpComponentInstance_members,                           /* tp_members */
  SkpComponentInstance_getseters,                         /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpComponentInstance_init,                    /* tp_init */
  0,                                                      /* tp_alloc */
  SkpComponentInstance_new,                               /* tp_new */
};

#endif
