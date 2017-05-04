#ifndef SKP_COMPONENT_DEFINITION_HPP
#define SKP_COMPONENT_DEFINITION_HPP

#include "common.hpp"

#include <SketchUpAPI/model/component_definition.h>

#include "drawing_element.hpp"

typedef struct {
  SkpDrawingElement skp_drawing_element;
  SUComponentDefinitionRef _su_def;
} SkpComponentDefinition;

static void SkpComponentDefinition_dealloc(SkpComponentDefinition* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpComponentDefinition__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity))
    ent_self->_su_entity = SUComponentDefinitionToEntity(((SkpComponentDefinition*)self)->_su_def);

  return ent_self->_su_entity;
}

static PyObject * SkpComponentDefinition_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpDrawingElementType.tp_new(type, args, kwds);

  SkpComponentDefinition *self = (SkpComponentDefinition*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpComponentDefinition__get_su_entity;

    self->_su_def = SU_INVALID;
  }

  return py_obj;
}

static int SkpComponentDefinition_init(SkpComponentDefinition *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpComponentDefinition_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpComponentDefinition_getentities(SkpComponentDefinition *self, void *closure);

static PyObject* SkpComponentDefinition_getname(SkpComponentDefinition *self, void *closure) {
  SKP_GET_STRING_BODY(SUComponentDefinitionGetName, _su_def, "cannot get name")
}

static int SkpComponentDefinition_setname(SkpComponentDefinition *self, PyObject *value, void *closure) {
  SKP_SET_STRING_BODY(SUComponentDefinitionSetName, _su_def, "cannot set name")
}

static PyObject* SkpComponentDefinition_getdescription(SkpComponentDefinition *self, void *closure) {
  SKP_GET_STRING_BODY(SUComponentDefinitionGetDescription, _su_def, "cannot get description")
}

static int SkpComponentDefinition_setdescription(SkpComponentDefinition *self, PyObject *value, void *closure) {
  SKP_SET_STRING_BODY(SUComponentDefinitionSetDescription, _su_def, "cannot set description")
}

static PyObject* SkpComponentDefinition_getguid(SkpComponentDefinition *self, void *closure) {
  SKP_GET_STRING_BODY(SUComponentDefinitionGetGuid, _su_def, "cannot get guid")
}

static PyObject* SkpComponentDefinition_getinstances(SkpComponentDefinition *self, void *closure);

static PyGetSetDef SkpComponentDefinition_getseters[] = {
  { "entities", (getter)SkpComponentDefinition_getentities, NULL,
    "entities", NULL},
  { "name", (getter)SkpComponentDefinition_getname, (setter)SkpComponentDefinition_setname,
    "name", NULL},
  { "description",
    (getter)SkpComponentDefinition_getdescription,
    (setter)SkpComponentDefinition_setdescription,
    "description", NULL},
  { "instances", (getter)SkpComponentDefinition_getinstances, NULL,
    "instances", NULL},
  { "guid", (getter)SkpComponentDefinition_getguid, NULL,
    "guid", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpComponentDefinition_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpComponentDefinitionType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.ComponentDefinition",                              /* tp_name */
  sizeof(SkpComponentDefinition),                         /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpComponentDefinition_dealloc,             /* tp_dealloc */
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
  "SketchUp ComponentDefinition",                         /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpComponentDefinition_methods,                         /* tp_methods */
  SkpComponentDefinition_members,                         /* tp_members */
  SkpComponentDefinition_getseters,                       /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpComponentDefinition_init,                  /* tp_init */
  0,                                                      /* tp_alloc */
  SkpComponentDefinition_new,                             /* tp_new */
};

#endif
