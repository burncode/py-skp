#include <Python.h>

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/vertex.h>
#include <vector>

#include "klass/model.c"
#include "klass/point3d.c"

static PyObject* create_model(PyObject *self, PyObject *args) {
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreate(&model);
  if (res != SU_ERROR_NONE) return NULL;

  SkpModel *py_model = (SkpModel*)PyObject_CallFunction((PyObject *) &SkpModelType, NULL);

  py_model->_su_model = model;

  return (PyObject*)py_model;
}

static PyMethodDef SkpMethods[] = {
  {"create_model", create_model, METH_NOARGS, "creates a new model"},

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

  return m;
}
