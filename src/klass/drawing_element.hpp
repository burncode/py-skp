#ifndef SKP_DRAWING_ELEMENT_HPP
#define SKP_DRAWING_ELEMENT_HPP

#include "common.hpp"

#include <SketchUpAPI/model/drawing_element.h>

#include "entity.hpp"

#include "bounding_box.hpp"
#include "layer.hpp"

typedef struct {
  SkpEntity skp_entity;
  SUDrawingElementRef (*get_su_drawing_el)(void*);
} SkpDrawingElement;

static SUDrawingElementRef SkpDrawingElement_get_su_drawing_el(void* self) {
  SUEntityRef su_entity = ((SkpEntity*)self)->get_su_entity(self);
  return SUDrawingElementFromEntity(su_entity);
}

static void SkpDrawingElement_dealloc(SkpDrawingElement* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject * SkpDrawingElement_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  PyObject *py_obj = (PyObject*)SkpEntityType.tp_new(type, args, kwds);

  SkpDrawingElement *self = (SkpDrawingElement*)py_obj;
  if (self != NULL) {
    self->get_su_drawing_el = &SkpDrawingElement_get_su_drawing_el;
  }

  return py_obj;
}

static int SkpDrawingElement_init(SkpDrawingElement *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyMemberDef SkpDrawingElement_members[] = {
  {NULL}  /* Sentinel */
};

static PyObject* SkpDrawingElement_getlayer(SkpDrawingElement *self, void *closure) {
  SKP_GET_SINGLE_ELEMENT(
    SkpLayer,
    SkpLayerType,
    SUDrawingElementGetLayer,
    get_su_drawing_el(self),
    _su_layer,
    "cannot get layer"
  )
}

static PyObject* SkpDrawingElement_getbounding_box(SkpDrawingElement *self, void *closure) {
  SUBoundingBox3D bbox;
  SUResult res = SUDrawingElementGetBoundingBox(self->get_su_drawing_el(self), &bbox);

  PyObject *py_bbox= (PyObject*)PyObject_CallFunction((PyObject*) &SkpBoundingBoxType, NULL);
  ((SkpBoundingBox*)py_bbox)->bbox = bbox;

  return py_bbox;
}

static PyGetSetDef SkpDrawingElement_getseters[] = {
  { "layer", (getter)SkpDrawingElement_getlayer, NULL,
    "layer", NULL},
  { "bounds", (getter)SkpDrawingElement_getbounding_box, NULL,
    "bounds", NULL},
  {NULL}  /* Sentinel */
};

static PyMethodDef SkpDrawingElement_methods[] = {
  {NULL}  /* Sentinel */
};

static PyTypeObject SkpDrawingElementType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "skp.DrawingElement",                                   /* tp_name */
  sizeof(SkpDrawingElement),                              /* tp_basicsize */
  0,                                                      /* tp_itemsize */
  (destructor)SkpDrawingElement_dealloc,                  /* tp_dealloc */
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               /*tp_flags */
  "SketchUp DrawingElement",                              /* tp_doc */
  0,                                                      /* tp_traverse */
  0,                                                      /* tp_clear */
  0,                                                      /* tp_richcompare */
  0,                                                      /* tp_weaklistoffset */
  0,                                                      /* tp_iter */
  0,                                                      /* tp_iternext */
  SkpDrawingElement_methods,                              /* tp_methods */
  SkpDrawingElement_members,                              /* tp_members */
  SkpDrawingElement_getseters,                            /* tp_getset */
  0,                                                      /* tp_base */
  0,                                                      /* tp_dict */
  0,                                                      /* tp_descr_get */
  0,                                                      /* tp_descr_set */
  0,                                                      /* tp_dictoffset */
  (initproc)SkpDrawingElement_init,                       /* tp_init */
  0,                                                      /* tp_alloc */
  SkpDrawingElement_new,                                  /* tp_new */
};

#endif
