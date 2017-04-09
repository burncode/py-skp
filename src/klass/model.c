#include <Python.h>
#include "structmember.h"

#include <SketchUpAPI/model/model.h>

#include "entities.c"

#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/vertex.h>
#include <vector>

typedef struct {
  PyObject_HEAD
  SUModelRef _su_model; 
  PyObject* entities;
} SkpModel;

static void SkpModel_dealloc(SkpModel* self) {
  SUModelRelease(&self->_su_model);
  //Py_XDECREF(self->_su_model);

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpModel_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpModel *self;

  self = (SkpModel*)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->_su_model = SU_INVALID;
  }

  return (PyObject *)self;
}

static int SkpModel_init(SkpModel *self, PyObject *args, PyObject *kwds) {
  return 0;
}

typedef struct {
  double x;
  double y;
} Pt;

static PyObject* SkpModel_getentities(SkpModel *self, void *closure) {
  SkpEntities *py_entities = (SkpEntities*)PyObject_CallFunction(
      (PyObject*) &SkpEntitiesType, NULL);

  SUResult res = SUModelGetEntities(self->_su_model, &py_entities->_su_entities);

  if (res == SU_ERROR_INVALID_INPUT) {
    PyErr_SetString(PyExc_TypeError, "SU_ERROR_INVALID_INPUT");
    Py_DECREF(py_entities);
    return NULL;
  }

  self->entities = (PyObject*)py_entities;

  Py_INCREF(self->entities);

  return self->entities;
}

static int SkpModel_setentities(SkpModel *self, PyObject *value, void *closure) {
  PyErr_SetString(PyExc_TypeError, "Cannot set entities.");
  return -1;
}

static PyMemberDef SkpModel_members[] = {
  {NULL}  /* Sentinel */
};

static PyGetSetDef SkpModel_getseters[] = {
  { "entities",
    (getter)SkpModel_getentities, (setter)SkpModel_setentities,
    "entities", 
    NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpModel_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpModelType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Model",                                            /* tp_name */
  sizeof(SkpModel),                                       /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpModel_dealloc,                           /* tp_dealloc */
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
  SkpModel_methods,                                       /* tp_methods */
  SkpModel_members,                                       /* tp_members */
  SkpModel_getseters,                                     /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpModel_init,                                /* tp_init */
  0,                                                      /* tp_alloc */
  SkpModel_new,                                           /* tp_new */
};
