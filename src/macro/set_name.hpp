#define SET_NAME_BODY(proc, _ref) { \
  char *name = PyUnicode_AsUTF8AndSize(value, NULL); \
  \
  if (name == NULL) { \
    PyErr_SetString(PyExc_TypeError, "cannot set name"); \
    return -1; \
  } \
  \
  SUResult res = proc(self->_ref, name); \
  if (checkerror(res, "cannot set name")) return -1; \
  \
  return 0; \
}
