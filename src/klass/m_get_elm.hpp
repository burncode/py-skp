#define GET_ELM_BODY( \
                     proc_get_elm_num, \
                     proc_get_elms, \
                     su_elm_type, \
                     __self_su_ref, \
                     __elm_su_ref, \
                     msg, \
                     py_struct, \
                     py_type \
                    ) { \
  size_t len; \
  \
  SUResult res_num = proc_get_elm_num(self->__self_su_ref, &len); \
  if (checkerror(res_num, msg)) return NULL; \
  \
  std::vector<su_elm_type> vec_elements(len); \
  \
  SUResult res = proc_get_elms(self->__self_su_ref, len, &vec_elements[0], &len); \
  if (checkerror(res, msg)) return NULL; \
  \
  PyObject *py_list= (PyObject*)PyObject_CallFunction((PyObject*)&PyList_Type, NULL); \
  \
  for (size_t i=0; i<len; ++i) { \
    py_struct *py_elm= (py_struct*)PyObject_CallFunction((PyObject*)&py_type, NULL); \
    py_elm->__elm_su_ref = vec_elements[i]; \
    int succ = PyList_Append(py_list, (PyObject*)py_elm); \
    if (succ < 0) { \
      PyErr_SetString(PyExc_RuntimeError, "Cannot append element to list"); \
      return NULL; \
    } \
  } \
  \
  return py_list; \
}
