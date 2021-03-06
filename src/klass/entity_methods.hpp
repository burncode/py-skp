#include "attribute_dictionary.hpp"

static PyObject* SkpEntity_getattribute_dictionaries(SkpEntity *self, void *closure) {
  self->get_su_entity(self); // ensure that _su_entity is assigned

  SKP_GET_ELEMENTS(
    SUEntityGetNumAttributeDictionaries,
    SUEntityGetAttributeDictionaries,
    SUAttributeDictionaryRef,
    _su_entity,
    _su_attrdict,
    "cannot get attribute_dictionaries",
    SkpAttributeDictionary,
    SkpAttributeDictionaryType
  )
}
