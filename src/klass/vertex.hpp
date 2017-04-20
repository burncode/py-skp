#ifndef SKP_VERTEX_HPP
#define SKP_VERTEX_HPP

#include "common.hpp"

#include <SketchUpAPI/model/vertex.h>

#include "point3d.hpp"

typedef struct {
  SkpDrawingElement skp_drawing_element;
  SUVertexRef _su_vertex;
} SkpVertex;

static void SkpVertex_dealloc(SkpVertex* self) {
  // TODO: dealloc members

  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpVertex__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity))
    ent_self->_su_entity = SUVertexToEntity(((SkpVertex*)self)->_su_vertex);

  return ent_self->_su_entity;
}

static PyObject * SkpVertex_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpDrawingElementType.tp_new(type, args, kwds);

  SkpVertex *self = (SkpVertex*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpVertex__get_su_entity;

    self->_su_vertex = SU_INVALID;
  }

  return py_obj;
}

static int SkpVertex_init(SkpVertex *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpVertex_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpVertex_getposition(SkpVertex *self, void *closure) {
  SUPoint3D pos;
  SUResult res = SUVertexGetPosition(self->_su_vertex, &pos);
  if (checkerror(res, "Cannot get position")) return NULL;

  PyObject *x = PyFloat_FromDouble(pos.x);
  PyObject *y = PyFloat_FromDouble(pos.y);
  PyObject *z = PyFloat_FromDouble(pos.z);

  if (x == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot get position");
    return NULL;
  }

  if (y == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot get position");
    return NULL;
  }

  if (z == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot get position");
    return NULL;
  }

  PyObject *py_point3d = (PyObject*)PyObject_CallFunction(
      (PyObject*) &SkpPoint3dType,  "OOO", x, y, z);

  if (py_point3d == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot get position");
    return NULL;
  }

  return py_point3d;
}

static PyObject* SkpVertex_getedges(SkpVertex *self, void *closure);
static PyObject* SkpVertex_getfaces(SkpVertex *self, void *closure);
static PyObject* SkpVertex_getloops(SkpVertex *self, void *closure);

static PyGetSetDef SkpVertex_getseters[] = {
  { "position", (getter)SkpVertex_getposition, NULL,
    "position", NULL},
  { "edges", (getter)SkpVertex_getedges, NULL,
    "edges", NULL},
  { "faces", (getter)SkpVertex_getfaces, NULL,
    "faces", NULL},
  { "loops", (getter)SkpVertex_getloops, NULL,
    "loops", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpVertex_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpVertexType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Vertex",                                           /* tp_name */
  sizeof(SkpVertex),                                      /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpVertex_dealloc,                          /* tp_dealloc */
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
  "SketchUp Vertex",                                      /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpVertex_methods,                                      /* tp_methods */
  SkpVertex_members,                                      /* tp_members */
  SkpVertex_getseters,                                    /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpVertex_init,                               /* tp_init */
  0,                                                      /* tp_alloc */
  SkpVertex_new,                                          /* tp_new */
};

#endif
