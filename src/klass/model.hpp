#ifndef SKP_MODEL_HPP
#define SKP_MODEL_HPP

#include "common.hpp"

#include <SketchUpAPI/model/model.h>

#include "entities.hpp"
#include "material.hpp"

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

static PyObject* SkpModel_getmaterials(SkpModel *self, void *closure) {
  GET_ELM_BODY(
    SUModelGetNumMaterials,
    SUModelGetMaterials,
    SUMaterialRef,
    _su_model,
    _su_material,
    "cannot get materials",
    SkpMaterial,
    SkpMaterialType
  )
}

static PyObject* SkpModel_getentities(SkpModel *self, void *closure) {
  SkpEntities *py_entities = (SkpEntities*)PyObject_CallFunction(
      (PyObject*) &SkpEntitiesType, NULL);

  SUResult res = SUModelGetEntities(self->_su_model, &py_entities->_su_entities);
  if (checkerror(res, "Cannot get position")) {
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
  { "entities", (getter)SkpModel_getentities, (setter)SkpModel_setentities,
    "entities", NULL},
  { "materials", (getter)SkpModel_getmaterials, NULL,
    "materials", NULL},
  {NULL}  /* Sentinel */
};

static PyObject * SkpModel_save(SkpModel* self) {
  SUModelSaveToFile(self->_su_model, "new_model.skp");

  return Py_None;
}

static PyMethodDef SkpModel_methods[] = {
  {"save", (PyCFunction)SkpModel_save, METH_NOARGS,
    "Save model"
  },
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

#endif
