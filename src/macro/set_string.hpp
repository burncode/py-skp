#define SKP_SET_STRING_BODY(proc, _ref, msg) { \
  char *name = PyUnicode_AsUTF8AndSize(value, NULL); \
  \
  if (name == NULL) { \
    PyErr_SetString(PyExc_TypeError, msg); \
    return -1; \
  } \
  \
  SUResult res = proc(self->_ref, name); \
  if (checkerror(res, msg)) return -1; \
  \
  return 0; \
}
