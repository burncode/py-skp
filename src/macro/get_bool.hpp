#define SKP_GET_BOOL_BODY(proc, _ref, msg) { \
  bool val; \
  SUResult res = proc(self->_ref, &val); \
  if (checkerror(res, msg)) return NULL; \
  \
  if (val) { \
    Py_RETURN_TRUE; \
  } else { \
    Py_RETURN_FALSE; \
  } \
}
