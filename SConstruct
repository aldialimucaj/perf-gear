env=Environment()
env.Append(CCFLAGS = ['-std=c99', '-Wall', '-g'])

pg_src = Glob('src/*.c')
duk_src = Glob('lib/*.c')

js_test_1 = 'js-tests/js-runner.c'

env.Library('perf-gear', pg_src)
env.Library('duktape', duk_src)

env.Program(js_test_1, LIBS=['perf-gear', 'duktape', 'm', 'pthread'], LIBPATH='.')