#ifndef SKP_FACE_HPP
#define SKP_FACE_HPP

#include "common.hpp"

#include <SketchUpAPI/model/face.h>
#include <vector>

#include "loop.hpp"
#include "edge.hpp"

typedef struct {
  PyObject_HEAD
  SUFaceRef _su_face;
  PyObject *outer_loop;
} SkpFace;

static void SkpFace_dealloc(SkpFace* self) {
  Py_XDECREF(self->outer_loop);

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpFace_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  SkpFace *self;

  self = (SkpFace*)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->_su_face = SU_INVALID;
  }

  return (PyObject *)self;
}

static int SkpFace_init(SkpFace *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpFace_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpFace_getedges(SkpFace *self, void *closure) {
  GET_ELM_BODY(
    SUFaceGetNumEdges,
    SUFaceGetEdges,
    SUEdgeRef,
    _su_face,
    _su_edge,
    "cannot get edges",
    SkpEdge,
    SkpEdgeType
  )
}

static PyObject* SkpFace_getouter_loop(SkpFace *self, void *closure) {
  SkpLoop *py_loop = (SkpLoop*)PyObject_CallFunction((PyObject*)&SkpLoopType, NULL);
  SULoopRef su_loop = SU_INVALID;


  SUResult res = SUFaceGetOuterLoop(self->_su_face, &su_loop);

  if (checkerror(res, "cannot get loop")) {
    Py_DECREF(py_loop);
    return NULL;
  }

  py_loop->_su_loop = su_loop;

  Py_INCREF(py_loop);
  self->outer_loop = (PyObject*)py_loop;

  return (PyObject*)py_loop;
}

static PyObject* SkpFace_getentityID(SkpFace *self, void *closure) {
  GET_ENTITY_BODY(_su_face, SUFaceToEntity)
}

static PyGetSetDef SkpFace_getseters[] = {
  { "outer_loop", (getter)SkpFace_getouter_loop, NULL,
    "outer_loop", NULL},
  { "edges", (getter)SkpFace_getedges, NULL,
    "edges", NULL},
  { "entityID", (getter)SkpFace_getentityID, NULL,
    "entityID", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpFace_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpFaceType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Face",                                             /* tp_name */
  sizeof(SkpFace),                                        /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpFace_dealloc,                            /* tp_dealloc */
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
  "SketchUp Face",                                        /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpFace_methods,                                        /* tp_methods */
  SkpFace_members,                                        /* tp_members */
  SkpFace_getseters,                                      /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpFace_init,                                 /* tp_init */
  0,                                                      /* tp_alloc */
  SkpFace_new,                                            /* tp_new */
};

#endif
