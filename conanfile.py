from conans import ConanFile, VisualStudioBuildEnvironment, tools
import os
import sys
import winreg
import json
from shutil import copyfile


class VSModulesTestConan(ConanFile):
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"

    path_config = os.path.join(os.path.dirname(__file__), 'config.json')
    with open(path_config) as json_file:
        data = json.load(json_file)
    skp_ver = data['skp_ver']
    py_include = data['py_include']
    py_lib = data['py_lib']

    def build(self):
        copyfile(self.path_root('src', 'script.py'), 'script.py')
        dll_dir = self.location_win_skp(self.skp_ver)
        if dll_dir:
            copyfile(os.path.join(dll_dir, 'SketchUpAPI.dll'), 'SketchUpAPI.dll')

        if self.settings.compiler == "Visual Studio":
            env_vars = VisualStudioBuildEnvironment(self).vars
            env_vars['CL'] += ' /I' + self.path_skp('headers')
            env_vars['CL'] += ' ' + self.path_skp_binaries('sketchup.lib')
            env_vars['CL'] += ' ' + self.path_skp_binaries('SketchUpAPI.lib')
            env_vars['CL'] += ' /I' + self.py_include
            env_vars['CL'] += ' ' + self.py_lib

            with tools.environment_append(env_vars):
                vcvars = tools.vcvars_command(self.settings)
                cmd = '%s && cl /EHsc ' % vcvars
                cmd += ' '.join([
                    self.path_root('src', 'main.cpp'),
                    self.path_root('src', 'util', 'checkerror.cpp'),
                    ])
                self.run(cmd)

    def location_win_skp(self, v='17'):
        loc = None
        try:
            key = winreg.OpenKey(
                    winreg.HKEY_LOCAL_MACHINE,
                    "SOFTWARE\SketchUp\SketchUp 20%s\InstallLocation" % v)
            loc = winreg.QueryValue(key, None)
        except FileNotFoundError:
            print("\n".join((
                "Could not locate SketchUp 20%s installation directory." % v,
                "Copy SketchUpAPI.dll manually.")))
        return loc

    def path_root(self, *args):
        return os.path.normpath(os.path.join(self.conanfile_directory, *args));

    def path_skp(self, *args):
        return self.path_root('ext/skp', *args)

    def path_skp_binaries(self, *args):
        return self.path_skp('binaries/sketchup/x64', *args)
