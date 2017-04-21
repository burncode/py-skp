#include <Python.h>
#include "structmember.h"

#include <vector>

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/typed_value.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/entity.h>

#include "../util/checkerror.h"

// Macros

#include "m_get_elm.hpp"

// helpers

#ifndef SKP_HELPERS_HPP
#define SKP_HELPERS_HPP

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

static PyObject* SUValueRefToPyObject(SUTypedValueRef ref) {
  SUTypedValueType type;
  SUResult res_type = SUTypedValueGetType(ref, &type);
  SUResult res;

  switch(type) {
    case SUTypedValueType_Empty :
      return Py_None;

    case SUTypedValueType_Byte :
      printf("%s", "Not Implemented: SUTypedValueType_Byte");
      break;
    case SUTypedValueType_Short :
      printf("%s", "Not Implemented: SUTypedValueType_Short");
      break;
    case SUTypedValueType_Int32 :
      int32_t int32_val;
      res = SUTypedValueGetInt32(ref, &int32_val);
      if (res != SU_ERROR_NONE) return NULL;
      return PyLong_FromSize_t((size_t) int32_val);

    case SUTypedValueType_Float :
      float f_val;
      res = SUTypedValueGetFloat(ref, &f_val);
      if (res != SU_ERROR_NONE) return NULL;
      return PyFloat_FromDouble((double) f_val);

    case SUTypedValueType_Double :
      double d_val;
      res = SUTypedValueGetDouble(ref, &d_val);
      if (res != SU_ERROR_NONE) return NULL;
      return PyFloat_FromDouble(d_val);

    case SUTypedValueType_Bool :
      bool b_val;
      res = SUTypedValueGetBool(ref, &b_val);
      if (res != SU_ERROR_NONE) return NULL;
      return (b_val) ? Py_True : Py_False;

    case SUTypedValueType_Color :
      printf("%s", "Not Implemented: SUTypedValueType_Color");
      break;
    case SUTypedValueType_Time :
      printf("%s", "Not Implemented: SUTypedValueType_Time");
      break;
    case SUTypedValueType_String : {
      SUStringRef str_ref = SU_INVALID;
      PyObject* py_str;
      bool err = false;

      res = SUStringCreate(&str_ref);
      if (res != SU_ERROR_NONE) err = true;

      res = SUTypedValueGetString(ref, &str_ref);
      if (res != SU_ERROR_NONE) err = true;

      if (!err) py_str = SUStringRefToPyString(str_ref);

      res = SUStringRelease(&str_ref);
      if (res != SU_ERROR_NONE) err = true;

      return (err) ? NULL : py_str;
    }

    case SUTypedValueType_Vector3D :
      printf("%s", "Not Implemented: SUTypedValueType_Vector3D");
      break;
    case SUTypedValueType_Array : {
      PyObject *py_list= (PyObject*)PyObject_CallFunction((PyObject*)&PyList_Type, NULL);
      bool err = false;

      size_t len=0;
      SUTypedValueGetNumArrayItems(ref, &len);

      std::vector<SUTypedValueRef> refs(len);

      res = SUTypedValueGetArrayItems(ref, len, &refs[0], &len);
      if (res != SU_ERROR_NONE) err = true;

      if (!err) {
        for (size_t i=0; i<len; ++i) {
          PyObject *py_elm = SUValueRefToPyObject(refs[i]);
          if (py_elm == NULL) { err = true; continue; }

          int succ = PyList_Append(py_list, py_elm);
          if (succ < 0) err = true;
        }
      }

      return (err) ? NULL : py_list;
    }
  }

  return NULL;
}

#endif
