#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/js-tests/js-runner.o \
	${OBJECTDIR}/lib/duktape.o \
	${OBJECTDIR}/src/collector.o \
	${OBJECTDIR}/src/db-measurement.o \
	${OBJECTDIR}/src/dispatcher.o \
	${OBJECTDIR}/src/dukbridge.o \
	${OBJECTDIR}/src/linked-list.o \
	${OBJECTDIR}/src/measurement2json.o \
	${OBJECTDIR}/src/perf-gear.o \
	${OBJECTDIR}/src/pg-utils.o \
	${OBJECTDIR}/src/queue.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f10 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=-Wall -Wextra

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -lm -lcurl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/js-tests/js-runner.o: js-tests/js-runner.c 
	${MKDIR} -p ${OBJECTDIR}/js-tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/js-tests/js-runner.o js-tests/js-runner.c

${OBJECTDIR}/lib/duktape.o: lib/duktape.c 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/duktape.o lib/duktape.c

${OBJECTDIR}/lib/duktape.h.gch: lib/duktape.h 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o "$@" lib/duktape.h

${OBJECTDIR}/src/collector.o: src/collector.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collector.o src/collector.c

${OBJECTDIR}/src/db-measurement.o: src/db-measurement.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/db-measurement.o src/db-measurement.c

${OBJECTDIR}/src/dispatcher.o: src/dispatcher.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dispatcher.o src/dispatcher.c

${OBJECTDIR}/src/dukbridge.o: src/dukbridge.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dukbridge.o src/dukbridge.c

${OBJECTDIR}/src/linked-list.o: src/linked-list.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/linked-list.o src/linked-list.c

${OBJECTDIR}/src/measurement2json.o: src/measurement2json.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/measurement2json.o src/measurement2json.c

${OBJECTDIR}/src/perf-gear.o: src/perf-gear.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/perf-gear.o src/perf-gear.c

${OBJECTDIR}/src/pg-utils.o: src/pg-utils.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pg-utils.o src/pg-utils.c

${OBJECTDIR}/src/queue.o: src/queue.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/queue.o src/queue.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f10: ${TESTDIR}/api-tests/api-general.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f10 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/collector-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/dispatcher-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f9: ${TESTDIR}/tests/db-measurement-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/dukbridge-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/linked-list-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/measurement2json-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/perf-gear-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/pg-utils-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/queue-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcunit 


${TESTDIR}/api-tests/api-general.o: api-tests/api-general.c 
	${MKDIR} -p ${TESTDIR}/api-tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/api-tests/api-general.o api-tests/api-general.c


${TESTDIR}/tests/collector-test.o: tests/collector-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/collector-test.o tests/collector-test.c


${TESTDIR}/tests/dispatcher-test.o: tests/dispatcher-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/dispatcher-test.o tests/dispatcher-test.c


${TESTDIR}/tests/db-measurement-test.o: tests/db-measurement-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/db-measurement-test.o tests/db-measurement-test.c


${TESTDIR}/tests/dukbridge-test.o: tests/dukbridge-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/dukbridge-test.o tests/dukbridge-test.c


${TESTDIR}/tests/linked-list-test.o: tests/linked-list-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/linked-list-test.o tests/linked-list-test.c


${TESTDIR}/tests/measurement2json-test.o: tests/measurement2json-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/measurement2json-test.o tests/measurement2json-test.c


${TESTDIR}/tests/perf-gear-test.o: tests/perf-gear-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/perf-gear-test.o tests/perf-gear-test.c


${TESTDIR}/tests/pg-utils-test.o: tests/pg-utils-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pg-utils-test.o tests/pg-utils-test.c


${TESTDIR}/tests/queue-test.o: tests/queue-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -std=c99 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/queue-test.o tests/queue-test.c


${OBJECTDIR}/js-tests/js-runner_nomain.o: ${OBJECTDIR}/js-tests/js-runner.o js-tests/js-runner.c 
	${MKDIR} -p ${OBJECTDIR}/js-tests
	@NMOUTPUT=`${NM} ${OBJECTDIR}/js-tests/js-runner.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/js-tests/js-runner_nomain.o js-tests/js-runner.c;\
	else  \
	    ${CP} ${OBJECTDIR}/js-tests/js-runner.o ${OBJECTDIR}/js-tests/js-runner_nomain.o;\
	fi

${OBJECTDIR}/lib/duktape_nomain.o: ${OBJECTDIR}/lib/duktape.o lib/duktape.c 
	${MKDIR} -p ${OBJECTDIR}/lib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lib/duktape.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/duktape_nomain.o lib/duktape.c;\
	else  \
	    ${CP} ${OBJECTDIR}/lib/duktape.o ${OBJECTDIR}/lib/duktape_nomain.o;\
	fi

${OBJECTDIR}/lib/duktape_nomain.h.gch: ${OBJECTDIR}/lib/duktape.h.gch lib/duktape.h 
	${MKDIR} -p ${OBJECTDIR}/lib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lib/duktape.h.gch`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o "$@" lib/duktape.h;\
	else  \
	    ${CP} ${OBJECTDIR}/lib/duktape.h.gch ${OBJECTDIR}/lib/duktape_nomain.h.gch;\
	fi

${OBJECTDIR}/src/collector_nomain.o: ${OBJECTDIR}/src/collector.o src/collector.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/collector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collector_nomain.o src/collector.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/collector.o ${OBJECTDIR}/src/collector_nomain.o;\
	fi

${OBJECTDIR}/src/db-measurement_nomain.o: ${OBJECTDIR}/src/db-measurement.o src/db-measurement.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/db-measurement.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/db-measurement_nomain.o src/db-measurement.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/db-measurement.o ${OBJECTDIR}/src/db-measurement_nomain.o;\
	fi

${OBJECTDIR}/src/dispatcher_nomain.o: ${OBJECTDIR}/src/dispatcher.o src/dispatcher.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/dispatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dispatcher_nomain.o src/dispatcher.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/dispatcher.o ${OBJECTDIR}/src/dispatcher_nomain.o;\
	fi

${OBJECTDIR}/src/dukbridge_nomain.o: ${OBJECTDIR}/src/dukbridge.o src/dukbridge.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/dukbridge.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dukbridge_nomain.o src/dukbridge.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/dukbridge.o ${OBJECTDIR}/src/dukbridge_nomain.o;\
	fi

${OBJECTDIR}/src/linked-list_nomain.o: ${OBJECTDIR}/src/linked-list.o src/linked-list.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/linked-list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/linked-list_nomain.o src/linked-list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/linked-list.o ${OBJECTDIR}/src/linked-list_nomain.o;\
	fi

${OBJECTDIR}/src/measurement2json_nomain.o: ${OBJECTDIR}/src/measurement2json.o src/measurement2json.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/measurement2json.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/measurement2json_nomain.o src/measurement2json.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/measurement2json.o ${OBJECTDIR}/src/measurement2json_nomain.o;\
	fi

${OBJECTDIR}/src/perf-gear_nomain.o: ${OBJECTDIR}/src/perf-gear.o src/perf-gear.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/perf-gear.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/perf-gear_nomain.o src/perf-gear.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/perf-gear.o ${OBJECTDIR}/src/perf-gear_nomain.o;\
	fi

${OBJECTDIR}/src/pg-utils_nomain.o: ${OBJECTDIR}/src/pg-utils.o src/pg-utils.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pg-utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pg-utils_nomain.o src/pg-utils.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pg-utils.o ${OBJECTDIR}/src/pg-utils_nomain.o;\
	fi

${OBJECTDIR}/src/queue_nomain.o: ${OBJECTDIR}/src/queue.o src/queue.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/queue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -std=c99 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/queue_nomain.o src/queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/queue.o ${OBJECTDIR}/src/queue_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f10 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
