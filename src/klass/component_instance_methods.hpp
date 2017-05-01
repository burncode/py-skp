#include "component_instance.hpp"

static PyObject* SkpComponentInstance_getattached_instances(SkpComponentInstance *self, void *closure) {
  SKP_GET_ELEMENTS(
    SUComponentInstanceGetNumAttachedInstances,
    SUComponentInstanceGetAttachedInstances,
    SUComponentInstanceRef,
    _su_ins,
    _su_ins,
    "cannot get attached_instances",
    SkpComponentInstance,
    SkpComponentInstanceType
  )
}
