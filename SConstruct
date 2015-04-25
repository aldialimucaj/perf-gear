lib_path = ['#src','#lib']

env=Environment(LIBPATH = lib_path)
env.Append(CCFLAGS = ['-std=c99', '-Wall', '-g'])

Export('env')
SConscript('lib/SConscript')
SConscript('src/SConscript')
SConscript('tests/SConscript')
SConscript('js-tests/SConscript')
