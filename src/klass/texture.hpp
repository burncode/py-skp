#ifndef SKP_TEXTURE_HPP
#define SKP_TEXTURE_HPP

#include "common.hpp"

#include <SketchUpAPI/model/texture.h>

#include "entity.hpp"

#define SKP_TEXTURE_DIMENSION(py_proc, var) { \
  size_t image_width, image_height; \
  double s_scale, t_scale; \
  \
  SUResult res = SUTextureGetDimensions( \
      self->_su_texture, &image_width, &image_height, &s_scale, &t_scale); \
  if (checkerror(res, "cannot get "#var)) return NULL; \
  \
  return py_proc(var); \
}

typedef struct {
  SkpEntity skp_entity;
  SUTextureRef _su_texture;
} SkpTexture;

static void SkpTexture_dealloc(SkpTexture* self) {
  // the parent object handles the deallocation
  // SUTextureRelease(&self->_su_texture);
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpTexture_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpEntityType.tp_new(type, args, kwds);

  SkpTexture *self = (SkpTexture*)py_obj;
  if (self != NULL) {
    self->_su_texture = SU_INVALID;
  }

  return py_obj;
}

static int SkpTexture_init(SkpTexture *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpTexture_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpTexture_getfilename(SkpTexture *self, void *closure) {
  SKP_GET_STRING_BODY(SUTextureGetFileName, _su_texture, "cannot get filename")
}

static PyObject* SkpTexture_getimage_width(SkpTexture *self, void *closure) {
  SKP_TEXTURE_DIMENSION(PyLong_FromSize_t, image_width)
}

static PyObject* SkpTexture_getimage_height(SkpTexture *self, void *closure) {
  SKP_TEXTURE_DIMENSION(PyLong_FromSize_t, image_height)
}

static PyObject* SkpTexture_gets_scale(SkpTexture *self, void *closure) {
  SKP_TEXTURE_DIMENSION(PyFloat_FromDouble, s_scale)
}

static PyObject* SkpTexture_gett_scale(SkpTexture *self, void *closure) {
  SKP_TEXTURE_DIMENSION(PyFloat_FromDouble, t_scale)
}

static PyGetSetDef SkpTexture_getseters[] = {
  { "filename", (getter)SkpTexture_getfilename, NULL,
    "filename", NULL},
  { "image_width", (getter)SkpTexture_getimage_width, NULL,
    "image_width", NULL},
  { "image_height", (getter)SkpTexture_getimage_height, NULL,
    "image_height", NULL},
  { "s_scale", (getter)SkpTexture_gets_scale, NULL,
    "s_scale", NULL},
  { "t_scale", (getter)SkpTexture_gett_scale, NULL,
    "t_scale", NULL},
  {NULL}  /* Sentinel */
};

static PyObject * SkpTexture_write(SkpTexture *self, PyObject *args) {
  char* path;
  if (!PyArg_ParseTuple(args, "s", &path)) return NULL;

  SUResult res = SUTextureWriteToFile(self->_su_texture, path);
  if (checkerror(res, "Cannot write texture")) return NULL;

  return Py_True;
}

static PyMethodDef SkpTexture_methods[] = {
  { "write", (PyCFunction)SkpTexture_write, METH_VARARGS,
    "writes texture to file" },
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpTextureType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Texture",                                          /* tp_name */
  sizeof(SkpTexture),                                     /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpTexture_dealloc,                         /* tp_dealloc */
  0,                                                      /* tp_print */
  0,                                                      /* tp_getattr */
  0,                                                      /* tp_setattr */
  0,                                                      /* tp_reserved */
  0,                                                      /* tp_repr */
  0,                                                      /* tp_as_number */
  0,                                                      /* tp_as_sequence */
  0,                                                      /* tp_as_mapping */
  0,                                                      /* tp_hash  */
  0,                                                      /* tp_call */
  0,                                                      /* tp_str */
  0,                                                      /* tp_getattro */
  0,                                                      /* tp_setattro */
  0,                                                      /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               /* tp_flags */
  "SketchUp Texture",                                     /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpTexture_methods,                                     /* tp_methods */
  SkpTexture_members,                                     /* tp_members */
  SkpTexture_getseters,                                   /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpTexture_init,                              /* tp_init */
  0,                                                      /* tp_alloc */
  SkpTexture_new,                                         /* tp_new */
};

#endif
