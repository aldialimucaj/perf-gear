lib_path = ['#src','#lib']

build_mode = ARGUMENTS.get('mode','debug')

if not ( build_mode in ['debug', 'release', 'cov']):
    print "Error, mode has to be debug, relase or cob. Your option was: " + build_mode
    Exit(1)

print "*** Compiling in " + build_mode + " mode ***"
debugcflags = ['-g','-Werror','-std=c99']
releasecflags = ['-Os','-Werror','-std=c99']
covcflags = ['-Os','-fprofile-arcs', '-ftest-coverage', '-Werror', '-std=c99']

env=Environment(LIBPATH = lib_path)

Export('env', 'build_mode', 'debugcflags', 'releasecflags', 'covcflags')

env.SConsignFile()

project = 'lib'
SConscript('lib/SConscript')

project = 'perf-gear'
SConscript('src/SConscript')

project = 'tests'
SConscript('tests/SConscript')

project = 'js-tests'
SConscript('js-tests/SConscript')
