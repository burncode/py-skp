#include <Python.h>

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/vertex.h>
#include <vector>

#include "klass/model.hpp"
#include "klass/entities.hpp"
#include "klass/face.hpp"
#include "klass/loop.hpp"
#include "klass/edge.hpp"
#include "klass/vertex.hpp"
#include "klass/vertex_methods.hpp"
#include "klass/entities_methods.hpp"

static PyObject* create_model(PyObject *self, PyObject *args) {
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreate(&model);
  if (res != SU_ERROR_NONE) return NULL;

  SkpModel *py_model = (SkpModel*)PyObject_CallFunction((PyObject *) &SkpModelType, NULL);

  py_model->_su_model = model;

  return (PyObject*)py_model;
}

static PyObject* read_model(PyObject *self, PyObject *args) {
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreateFromFile(&model, "model.skp");
  if (checkerror(res, "Cannot read model")) return NULL;

  SkpModel *py_model = (SkpModel*)PyObject_CallFunction((PyObject *) &SkpModelType, NULL);

  py_model->_su_model = model;

  return (PyObject*)py_model;
}

static PyMethodDef SkpMethods[] = {
  {"create_model", create_model, METH_NOARGS, "creates a new model"},
  {"read_model", read_model, METH_NOARGS, "reads model from file"},
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef skpmodule = {
   PyModuleDef_HEAD_INIT, "skp", NULL, -1, SkpMethods
};

PyMODINIT_FUNC PyInit_skp(void) {
  PyObject *m;

  m = PyModule_Create(&skpmodule);
  if (m == NULL) return NULL;

  if (PyType_Ready(&SkpModelType) < 0) return NULL;
  Py_INCREF(&SkpModelType);
  PyModule_AddObject(m, "Model", (PyObject *)&SkpModelType);

  if (PyType_Ready(&SkpEntitiesType) < 0) return NULL;
  Py_INCREF(&SkpEntitiesType);
  PyModule_AddObject(m, "Entities", (PyObject *)&SkpEntitiesType);

  if (PyType_Ready(&SkpPoint3dType) < 0) return NULL;
  Py_INCREF(&SkpPoint3dType);
  PyModule_AddObject(m, "Point3d", (PyObject *)&SkpPoint3dType);

  if (PyType_Ready(&SkpFaceType) < 0) return NULL;
  Py_INCREF(&SkpFaceType);
  PyModule_AddObject(m, "Face", (PyObject *)&SkpFaceType);

  if (PyType_Ready(&SkpLoopType) < 0) return NULL;
  Py_INCREF(&SkpLoopType);
  PyModule_AddObject(m, "Loop", (PyObject *)&SkpLoopType);

  if (PyType_Ready(&SkpEdgeType) < 0) return NULL;
  Py_INCREF(&SkpEdgeType);
  PyModule_AddObject(m, "Edge", (PyObject *)&SkpEdgeType);

  if (PyType_Ready(&SkpVertexType) < 0) return NULL;
  Py_INCREF(&SkpVertexType);
  PyModule_AddObject(m, "Vertex", (PyObject *)&SkpVertexType);

  return m;
}
