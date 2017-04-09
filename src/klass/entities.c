#include <Python.h>
#include "structmember.h"

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/model/entities.h>

typedef struct {
  PyObject_HEAD
  SUEntitiesRef _su_entities; 
} SkpEntities;

static void SkpEntities_dealloc(SkpEntities* self) {
  //Py_XDECREF(self->_su_entities);

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpEntities_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpEntities *self;

  self = (SkpEntities*)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->_su_entities = SU_INVALID;
  }

  return (PyObject *)self;
}

static int SkpEntities_init(SkpEntities *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpEntities_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject * SkpEntities_create_face(SkpEntities* self, PyObject *args) {
  return Py_None;
}

static PyMethodDef SkpEntities_methods[] = {
  {"create_face", (PyCFunction)SkpEntities_create_face, METH_VARARGS,
    "Create a face with outer_loop"
  },
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpEntitiesType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Entities",                                         /* tp_name */
  sizeof(SkpEntities),                                    /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpEntities_dealloc,                        /* tp_dealloc */
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
  SkpEntities_methods,                                    /* tp_methods */
  SkpEntities_members,                                    /* tp_members */
  0,                                                      /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpEntities_init,                             /* tp_init */
  0,                                                      /* tp_alloc */
  SkpEntities_new,                                        /* tp_new */
};
