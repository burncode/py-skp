#ifndef SKP_ATTRIBUTE_DICTIONARY_HPP
#define SKP_ATTRIBUTE_DICTIONARY_HPP

#include "common.hpp"

#include <SketchUpAPI/model/attribute_dictionary.h>

#include "entity.hpp"

typedef struct {
  SkpEntity skp_entilty;
  SUAttributeDictionaryRef _su_attrdict;
} SkpAttributeDictionary;

static void SkpAttributeDictionary_dealloc(SkpAttributeDictionary* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpAttributeDictionary__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity)) {
    ent_self->_su_entity = SUAttributeDictionaryToEntity(
      ((SkpAttributeDictionary*)self)->_su_attrdict
    );
  }

  return ent_self->_su_entity;
}

static PyObject * SkpAttributeDictionary_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpEntityType.tp_new(type, args, kwds);

  SkpAttributeDictionary *self = (SkpAttributeDictionary*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpAttributeDictionary__get_su_entity;

    self->_su_attrdict = SU_INVALID;
  }

  return py_obj;
}

static int SkpAttributeDictionary_init(SkpAttributeDictionary *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpAttributeDictionary_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpAttributeDictionary_getkeys(SkpAttributeDictionary *self, void *closure) {
  size_t len=0;
  SUResult res_len = SUAttributeDictionaryGetNumKeys(self->_su_attrdict, &len);
  if (checkerror(res_len, "cannot get keys")) return NULL;

  std::vector<SUStringRef> refs(len);

  for (size_t i=0; i<len; ++i) {
    SUStringCreate(&refs[i]);
  }

  SUResult res = SUAttributeDictionaryGetKeys(self->_su_attrdict, len, &refs[0], &len);
  if (checkerror(res, "cannot get keys")) return NULL;

  PyObject *py_list= (PyObject*)PyObject_CallFunction((PyObject*)&PyList_Type, NULL);
  bool err = false;

  for (size_t i=0; i<len; ++i) {
    PyObject *py_elm = SUStringRefToPyString(refs[i]);
    if (py_elm == NULL) {
      err = true;
      continue;
    }

    int succ = PyList_Append(py_list, py_elm);
    if (succ < 0) err = true;
  }

  for (size_t i=0; i<len; ++i) {
    SUStringRelease(&refs[i]);
  }

  if (err) {
    PyErr_SetString(PyExc_RuntimeError, "cannot get keys");
    Py_DECREF(py_list);
    return NULL;
  }

  return py_list;
}

static PyObject* SkpAttributeDictionary_getname(SkpAttributeDictionary *self, void *closure) {
  GET_NAME_BODY(SUAttributeDictionaryGetName, _su_attrdict)
}

static PyGetSetDef SkpAttributeDictionary_getseters[] = {
  { "name", (getter)SkpAttributeDictionary_getname, NULL,
    "name", NULL},
  { "keys", (getter)SkpAttributeDictionary_getkeys, NULL,
    "keys", NULL},
  {NULL}  /* Sentinel */
};

static PyObject * SkpAttributeDictionary_get_value(
    SkpAttributeDictionary *self, PyObject *args, PyObject *kwds) {
  char* key;
  if (!PyArg_ParseTuple(args, "s", &key)) return NULL;

  SUTypedValueRef value_out = SU_INVALID;

  SUResult res_create = SUTypedValueCreate(&value_out);
  if (checkerror(res_create, "cannot get value")) return NULL;

  SUResult res = SUAttributeDictionaryGetValue(self->_su_attrdict, key, &value_out);
  if (res == SU_ERROR_NO_DATA) {
    SUTypedValueRelease(&value_out);
    return Py_None;
  }
  if (checkerror(res, "cannot get value")) return NULL;

  PyObject *py_val = SUValueRefToPyObject(value_out);

  SUResult res_release = SUTypedValueRelease(&value_out);
  if (checkerror(res_release, "cannot get value")) return NULL;

  return py_val;
}

static PyMethodDef SkpAttributeDictionary_methods[] = {
  { "get_value", (PyCFunction)SkpAttributeDictionary_get_value, METH_VARARGS,
    "get_value" },
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpAttributeDictionaryType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.AttributeDictionary",                              /* tp_name */
  sizeof(SkpAttributeDictionary),                         /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpAttributeDictionary_dealloc,             /* tp_dealloc */
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
  "SketchUp AttributeDictionary",                         /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpAttributeDictionary_methods,                         /* tp_methods */
  SkpAttributeDictionary_members,                         /* tp_members */
  SkpAttributeDictionary_getseters,                       /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpAttributeDictionary_init,                  /* tp_init */
  0,                                                      /* tp_alloc */
  SkpAttributeDictionary_new,                             /* tp_new */
};

#endif
