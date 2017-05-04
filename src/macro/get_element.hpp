#define SKP_GET_SINGLE_ELEMENT( \
                                PyKlass, \
                                PyKlassType, \
                                proc, \
                                _self_ref, \
                                _target_ref, \
                                msg ) { \
  PyKlass *py_obj = (PyKlass*)PyObject_CallFunction((PyObject*)&PyKlassType, NULL); \
  \
  SUResult res = proc(self->_self_ref, &py_obj->_target_ref); \
  if (res == SU_ERROR_NO_DATA) { \
    Py_DECREF(py_obj); \
    Py_RETURN_NONE; \
  } \
  if (checkerror(res, msg)) { \
    Py_DECREF(py_obj); \
    return NULL; \
  } \
  \
  return (PyObject*)py_obj; \
}
