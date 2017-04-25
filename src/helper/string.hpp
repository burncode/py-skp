#ifndef SKP_HELPER_STRING_HPP
#define SKP_HELPER_STRING_HPP

static PyObject* SUStringRefToPyString(SUStringRef ref) {
  size_t len = 0;

  SUResult res_len = SUStringGetUTF8Length(ref, &len);
  if (res_len != SU_ERROR_NONE) return NULL;

  char* char_arr = new char[len + 1];
  SUResult res_char = SUStringGetUTF8(ref, len + 1, char_arr, &len);
  if (res_char != SU_ERROR_NONE) return NULL;

  PyObject *py_str = PyUnicode_FromFormat("%s", char_arr);
  delete []char_arr;

  return py_str;
}

#endif
