#ifndef SKP_EDGE_HPP
#define SKP_EDGE_HPP

#include "common.hpp"

#include <SketchUpAPI/model/edge.h>

#include "vertex.hpp"

typedef struct {
  PyObject_HEAD
  SUEdgeRef _su_edge;
  PyObject* start;
  PyObject* end;
} SkpEdge;

static void SkpEdge_dealloc(SkpEdge* self) {
  // TODO: dealloc members
  Py_XDECREF(self->start);
  Py_XDECREF(self->end);

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpEdge_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpEdge *self;

  self = (SkpEdge*)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->_su_edge = SU_INVALID;
    self->start = NULL;
    self->end = NULL;
  }

  return (PyObject *)self;
}

static int SkpEdge_init(SkpEdge *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpEdge_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpEdge_getstart(SkpEdge *self, void *closure) {
  if (self->start) return self->start;

  PyObject *py_vertex = (PyObject*)PyObject_CallFunction(
      (PyObject*) &SkpVertexType, NULL);

  SUResult res = SUEdgeGetStartVertex(self->_su_edge, &((SkpVertex*)py_vertex)->_su_vertex);
  if (checkerror(res, "Cannot get vertex")) return NULL;

  self->start = py_vertex;

  return py_vertex;
}

static PyObject* SkpEdge_getend(SkpEdge *self, void *closure) {
  if (self->end) return self->end;

  PyObject *py_vertex = (PyObject*)PyObject_CallFunction(
      (PyObject*) &SkpVertexType, NULL);

  SUResult res = SUEdgeGetEndVertex(self->_su_edge, &((SkpVertex*)py_vertex)->_su_vertex);
  if (checkerror(res, "Cannot get vertex")) return NULL;

  return py_vertex;
}

static PyObject* tmp(SkpEdge *self, void *closure) {
  printf("%p", &self->_su_edge);
  return Py_None;
}

static PyObject* SkpEdge_getentityID(SkpEdge *self, void *closure) {
  GET_ENTITY_BODY(_su_edge, SUEdgeToEntity)
}

static PyGetSetDef SkpEdge_getseters[] = {
  { "start", (getter)SkpEdge_getstart, NULL,
    "start", NULL},
  { "end", (getter)SkpEdge_getend, NULL,
    "end", NULL},
  { "tmp", (getter)tmp, NULL,
    "tmp", NULL},
  { "entityID", (getter)SkpEdge_getentityID, NULL,
    "entityID", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpEdge_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpEdgeType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Edge",                                             /* tp_name */
  sizeof(SkpEdge),                                        /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpEdge_dealloc,                            /* tp_dealloc */
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
  "SketchUp Edge",                                        /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpEdge_methods,                                        /* tp_methods */
  SkpEdge_members,                                        /* tp_members */
  SkpEdge_getseters,                                      /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpEdge_init,                                 /* tp_init */
  0,                                                      /* tp_alloc */
  SkpEdge_new,                                            /* tp_new */
};

#endif
