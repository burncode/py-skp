#include <Python.h>
#include <SketchUpAPI/initialize.h>

#include "skpmodule.cpp"

#include <stdio.h>

int main(int argc, char *argv[]) {
  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == NULL) {
    fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
    exit(1);
  }
  Py_SetProgramName(program);  /* optional but recommended */

  PyImport_AppendInittab("skp", &PyInit_skp);

  SUInitialize();

  Py_Initialize();

  FILE *file = _Py_fopen_obj(Py_BuildValue("s", "script.py"), "r+");
  if(file == NULL) {
    printf("%s", "script.py Not Found.");
  } else {
    PyRun_SimpleFileEx(file, "script.py", 1);
  }

  if (Py_FinalizeEx() < 0) {
    exit(120);
  }
  PyMem_RawFree(program);

  SUTerminate();

  return 0;
}
