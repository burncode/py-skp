#include "checkerror.h"

bool checkerror(SUResult res, char *msg) {
  if (res == SU_ERROR_NONE) return false;

  char *err;
  switch(res) {
    case SU_ERROR_NONE :
      err = "SU_ERROR_NONE";
      break;

    case SU_ERROR_NULL_POINTER_INPUT :
      err = "SU_ERROR_NULL_POINTER_INPUT";
      break;

    case SU_ERROR_INVALID_INPUT :
      err = "SU_ERROR_INVALID_INPUT";
      break;

    case SU_ERROR_NULL_POINTER_OUTPUT :
      err = "SU_ERROR_NULL_POINTER_OUTPUT";
      break;

    case SU_ERROR_INVALID_OUTPUT :
      err = "SU_ERROR_INVALID_OUTPUT";
      break;

    case SU_ERROR_OVERWRITE_VALID :
      err = "SU_ERROR_OVERWRITE_VALID";
      break;

    case SU_ERROR_GENERIC :
      err = "SU_ERROR_GENERIC";
      break;

    case SU_ERROR_SERIALIZATION :
      err = "SU_ERROR_SERIALIZATION";
      break;

    case SU_ERROR_OUT_OF_RANGE :
      err = "SU_ERROR_OUT_OF_RANGE";
      break;

    case SU_ERROR_NO_DATA :
      err = "SU_ERROR_NO_DATA";
      break;

    case SU_ERROR_INSUFFICIENT_SIZE :
      err = "SU_ERROR_INSUFFICIENT_SIZE";
      break;

    case SU_ERROR_UNKNOWN_EXCEPTION :
      err = "SU_ERROR_UNKNOWN_EXCEPTION";
      break;

    case SU_ERROR_MODEL_INVALID :
      err = "SU_ERROR_MODEL_INVALID";
      break;

    case SU_ERROR_MODEL_VERSION :
      err = "SU_ERROR_MODEL_VERSION";
      break;

    case SU_ERROR_LAYER_LOCKED :
      err = "SU_ERROR_LAYER_LOCKED";
      break;

    case SU_ERROR_DUPLICATE :
      err = "SU_ERROR_DUPLICATE";
      break;

    case SU_ERROR_PARTIAL_SUCCESS :
      err = "SU_ERROR_PARTIAL_SUCCESS";
      break;

    case SU_ERROR_UNSUPPORTED :
      err = "SU_ERROR_UNSUPPORTED";
      break;

    case SU_ERROR_INVALID_ARGUMENT :
      err = "SU_ERROR_INVALID_ARGUMENT";
      break;
  }

  char buffer[255];
  snprintf(buffer, 255, "%s %s", err, msg);
  PyErr_SetString(PyExc_RuntimeError, buffer);

  return true;
}

/* ~~ruby~~
data = """
SU_ERROR_NONE
SU_ERROR_NULL_POINTER_INPUT
SU_ERROR_INVALID_INPUT
SU_ERROR_NULL_POINTER_OUTPUT
SU_ERROR_INVALID_OUTPUT
SU_ERROR_OVERWRITE_VALID
SU_ERROR_GENERIC
SU_ERROR_SERIALIZATION
SU_ERROR_OUT_OF_RANGE
SU_ERROR_NO_DATA
SU_ERROR_INSUFFICIENT_SIZE
SU_ERROR_UNKNOWN_EXCEPTION
SU_ERROR_MODEL_INVALID
SU_ERROR_MODEL_VERSION
SU_ERROR_LAYER_LOCKED
SU_ERROR_DUPLICATE
SU_ERROR_PARTIAL_SUCCESS
SU_ERROR_UNSUPPORTED
SU_ERROR_INVALID_ARGUMENT
"""

require 'erb'

template = '''
switch(res) {
  <% errors.each do |str| %>
  case <%=str%> :
    err = "<%=str%>";
    break;
  <% end %>
}
'''

errors = data.split()

renderer = ERB.new(template)
output = renderer.result(binding)

puts output
~~ruby~~ */
