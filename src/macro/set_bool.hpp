#define SKP_SET_BOOL_BODY(proc, _ref, msg) { \
  if (!PyBool_Check(value)) { \
    PyErr_SetString(PyExc_TypeError, msg); \
    return -1; \
  } \
  \
  bool val = !!PyObject_IsTrue(value); \
  SUResult res = proc(self->_ref, val); \
  if (checkerror(res, msg)) return -1; \
  \
  return 0; \
}
