#ifndef SKP_MATERIAL_HPP
#define SKP_MATERIAL_HPP

#include "common.hpp"

#include <SketchUpAPI/model/material.h>

#include "color.hpp"
#include "entity.hpp"
#include "texture.hpp"

typedef struct {
  SkpEntity skp_entilty;
  SUMaterialRef _su_material;
} SkpMaterial;

static void SkpMaterial_dealloc(SkpMaterial* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static SUEntityRef SkpMaterial__get_su_entity(void *self) {
  SkpEntity *ent_self = (SkpEntity*)self;

  if (!SUIsValid(ent_self->_su_entity)) {
    ent_self->_su_entity = SUMaterialToEntity(((SkpMaterial*)self)->_su_material);
  }

  return ent_self->_su_entity;
}

static PyObject * SkpMaterial_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpEntityType.tp_new(type, args, kwds);

  SkpMaterial *self = (SkpMaterial*)py_obj;
  if (self != NULL) {
    ((SkpEntity*)self)->get_su_entity = &SkpMaterial__get_su_entity;

    self->_su_material = SU_INVALID;
  }

  return py_obj;
}

static int SkpMaterial_init(SkpMaterial *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpMaterial_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpMaterial_getname(SkpMaterial *self, void *closure) {
  SKP_GET_STRING_BODY(SUMaterialGetName, _su_material, "cannot get name")
}

static int SkpMaterial_setname(SkpMaterial *self, PyObject *value, void *closure) {
  SET_NAME_BODY(SUMaterialSetName, _su_material)
}

static PyObject* SkpMaterial_getuse_alpha(SkpMaterial *self, void *closure) {
  bool alpha;

  SUResult res = SUMaterialGetUseOpacity(self->_su_material, &alpha);
  if (checkerror(res, "cannot get use_alpha")) return NULL;

  return (alpha) ? Py_True : Py_False;
}

static PyObject* SkpMaterial_getcolorize_type(SkpMaterial *self, void *closure) {
  SUMaterialType type;

  SUResult res = SUMaterialGetType(self->_su_material, &type);
  if (checkerror(res, "cannot get materialType")) return NULL;

  return PyLong_FromLong((long)type);
}

static int SkpMaterial_setcolorize_type(SkpMaterial *self, PyObject *value, void *closure) {
  int type = (int)PyLong_AsLong(value);

  if (!type) {
    PyErr_SetString(PyExc_TypeError, "Invalid colorization type");
    return -1;
  }

  if (!SUMaterialTypeIntValid(type)) {
    PyErr_SetString(PyExc_TypeError, "Invalid colorization type");
    return -1;
  }

  SUResult res = SUMaterialSetType(self->_su_material, (SUMaterialType)type);
  if (checkerror(res, "cannot set colorization type")) return -1;

  return 0;
}

static PyObject* SkpMaterial_getcolor(SkpMaterial *self, void *closure) {
  SUColor su_color;
  SUResult res = SUMaterialGetColor(self->_su_material, &su_color);
  if (checkerror(res, "cannot get color")) return NULL;

  PyObject *py_color= PyObject_CallFunction((PyObject*)&SkpColorType,
      "bbbb",
      su_color.red,
      su_color.green,
      su_color.blue,
      su_color.alpha);

  if (py_color == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot get color");
    return NULL;
  }

  Py_INCREF(py_color);

  return py_color;
}

static int SkpMaterial_setcolor(SkpMaterial *self, PyObject *value, void *closure) {
  if (PyObject_TypeCheck(value, (PyTypeObject*)&SkpColorType)) {
    SUColor *color = (SUColor*)&((SkpColor*)value)->red;

    SUResult res = SUMaterialSetColor(self->_su_material, color);
    if (checkerror(res, "cannot set color")) return -1;

    return 0;
  } else {
    PyErr_SetString(PyExc_TypeError, "argument is not a skp.Color");
    return -1;
  }
}

static PyObject* SkpMaterial_gettexture(SkpMaterial *self, void *closure) {
  SKP_GET_SINGLE_ELEMENT(
    SkpTexture,
    SkpTextureType,
    SUMaterialGetTexture,
    _su_material,
    _su_texture,
    "cannot get texture"
  )
}

static int SkpMaterial_settexture(SkpMaterial *self, PyObject *value, void *closure) {
  return -1;
}

static PyGetSetDef SkpMaterial_getseters[] = {
  { "name", (getter)SkpMaterial_getname, (setter)SkpMaterial_setname,
    "name", NULL},
  { "colorize_type", (getter)SkpMaterial_getcolorize_type, (setter)SkpMaterial_setcolorize_type,
    "colorize_type", NULL},
  { "use_alpha", (getter)SkpMaterial_getuse_alpha, NULL,
    "use_alpha", NULL},
  { "color", (getter)SkpMaterial_getcolor, (setter)SkpMaterial_setcolor,
    "color", NULL},
  { "texture", (getter)SkpMaterial_gettexture, (setter)SkpMaterial_settexture,
    "texture", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpMaterial_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpMaterialType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.Material",                                         /* tp_name */
  sizeof(SkpMaterial),                                    /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpMaterial_dealloc,                        /* tp_dealloc */
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
  "SketchUp Material",                                    /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpMaterial_methods,                                    /* tp_methods */
  SkpMaterial_members,                                    /* tp_members */
  SkpMaterial_getseters,                                  /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpMaterial_init,                             /* tp_init */
  0,                                                      /* tp_alloc */
  SkpMaterial_new,                                        /* tp_new */
};

#endif
