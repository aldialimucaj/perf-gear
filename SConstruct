
import SCons
import os

build_mode = ARGUMENTS.get('mode','debug')

if not ( build_mode in ['debug', 'release', 'cov']):
    print "Error, mode has to be debug, relase or cob. Your option was: " + build_mode
    Exit(1)

print "*** Compiling in " + build_mode + " mode ***"
debugcflags = ['-g','-Werror', '-Wall', '-Wextra', '-std=c99']
releasecflags = ['-Os','-Werror', '-Wall', '-Wextra', '-std=c99']
covcflags = ['-Os','-fprofile-arcs', '-ftest-coverage', '-Werror', '-Wall', '-Wextra', '-std=c99']

lib_path = ['#build/' + build_mode + '/lib', '#build/' + build_mode + '/src']
env=Environment(LIBPATH = lib_path)

Export('env', 'build_mode', 'debugcflags', 'releasecflags', 'covcflags')

env.SConsignFile()


# define the custom function
from SCons.Script.SConscript import SConsEnvironment
SConsEnvironment.Chmod = SCons.Action.ActionFactory(os.chmod, lambda dest, mode: 'Chmod("%s", 0%o)' % (dest, mode))

def InstallPerm(env, dest, files, perm):
    obj = env.Install(dest, files)
    for i in obj:
        env.AddPostAction(i, env.Chmod(str(i), perm))
    return dest

# put this function "in" scons
SConsEnvironment.InstallPerm = InstallPerm

SConsEnvironment.InstallHeader = lambda env, dest, files: InstallPerm(env, dest, files, 0644)

project = 'lib'
SConscript('lib/SConscript', variant_dir='#build/' + build_mode + '/'+project, duplicate=0)

project = 'perf-gear'
SConscript('src/SConscript', variant_dir='#build/' + build_mode + '/src', duplicate=0)

project = 'tests'
SConscript('tests/SConscript', variant_dir='#build/' + build_mode + '/'+project, duplicate=0)

project = 'js-tests'
SConscript('js-tests/SConscript', variant_dir='#build/' + build_mode + '/'+project, duplicate=0)

project = 'api-tests'
SConscript('api-tests/SConscript', variant_dir='#build/' + build_mode + '/'+project, duplicate=0)