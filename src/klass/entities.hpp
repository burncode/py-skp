#ifndef SKP_ENTITIES_HPP
#define SKP_ENTITIES_HPP

#include "common.hpp"

#include "face.hpp"
#include "point3d.hpp"

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
  SkpFace *py_face = (SkpFace*)PyObject_CallFunction(
      (PyObject*) &SkpFaceType, NULL);

  if (py_face == NULL) {
    //TODO: set error
    return NULL;
  }

  int len;
  PyObject *py_list;
  SkpPoint3d *py_pt;

  if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &py_list)) return NULL;

  len = PyList_Size(py_list);

  if (len < 0) {
    PyErr_SetString(PyExc_TypeError, "argument not a list");
    return NULL;
  }

  std::vector<SUPoint3D> vertices(len);

  for (size_t i=0; i<len; i++){
    py_pt = (SkpPoint3d*)PyList_GetItem(py_list, i);
    vertices[i].x = PyFloat_AsDouble(py_pt->x);
    vertices[i].y = PyFloat_AsDouble(py_pt->y);
    vertices[i].z = PyFloat_AsDouble(py_pt->z);
  }

  SULoopInputRef outer_loop = SU_INVALID;
  SUResult res_loop = SULoopInputCreate(&outer_loop);
  if (checkerror(res_loop, "Cannot create loop")) return NULL;

  for (size_t i=0; i<len; ++i) {
    SUResult res = SULoopInputAddVertexIndex(outer_loop, i);
    if (checkerror(res, "Cannot create loop")) return NULL;
  }

  SUFaceRef face = SU_INVALID;
  SUResult res = SUFaceCreate(&face, (SUPoint3D*)&vertices[0], &outer_loop);
  if (checkerror(res, "Cannot create face")) return NULL;

  SUResult res_ent = SUEntitiesAddFaces(self->_su_entities, 1, &face);
  if (checkerror(res_ent, "Cannot add face")) return NULL;

  py_face->_su_face = face;

  return (PyObject*)py_face;
}

static PyObject* SkpEntities_getfaces(SkpEntities *self, void *closure);

static PyMethodDef SkpEntities_methods[] = {
  {"create_face", (PyCFunction)SkpEntities_create_face, METH_VARARGS,
    "Create a face with outer_loop"
  },
  {NULL}  /* Sentinel */
};

static PyGetSetDef SkpEntities_getseters[] = {
  { "faces", (getter)SkpEntities_getfaces, NULL,
    "faces", NULL},
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
  SkpEntities_getseters,                                  /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpEntities_init,                             /* tp_init */
  0,                                                      /* tp_alloc */
  SkpEntities_new,                                        /* tp_new */
};

#endif
