#define GET_NAME_BODY(proc, __self_su_ref) { \
  bool err = false; \
  \
  SUStringRef su_str = SU_INVALID; \
  SUResult res_create = SUStringCreate(&su_str); \
  if (checkerror(res_create, "cannot get name")) err = true; \
  \
  SUResult res_str = proc(self->__self_su_ref, &su_str); \
  if (checkerror(res_str, "cannot get name")) err = true; \
  \
  PyObject *py_str = SUStringRefToPyString(su_str); \
  if (py_str == NULL) { \
    err = true; \
    PyErr_SetString(PyExc_RuntimeError, "cannot get name"); \
  } \
  \
  SUResult res_free = SUStringRelease(&su_str); \
  if (checkerror(res_free, "cannot get name")) err = true; \
  \
  if (err) { \
    Py_XDECREF(py_str); \
    return NULL; \
  }; \
  \
  return py_str; \
}
