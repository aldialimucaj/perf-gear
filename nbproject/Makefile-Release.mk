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
	${OBJECTDIR}/src/collector.o \
	${OBJECTDIR}/src/dispatcher.o \
	${OBJECTDIR}/src/linked-list.o \
	${OBJECTDIR}/src/measurement2json.o \
	${OBJECTDIR}/src/perf-gear.o \
	${OBJECTDIR}/src/pg-utils.o \
	${OBJECTDIR}/src/queue.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperf-gear.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/collector.o: src/collector.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collector.o src/collector.c

${OBJECTDIR}/src/dispatcher.o: src/dispatcher.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dispatcher.o src/dispatcher.c

${OBJECTDIR}/src/linked-list.o: src/linked-list.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/linked-list.o src/linked-list.c

${OBJECTDIR}/src/measurement2json.o: src/measurement2json.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/measurement2json.o src/measurement2json.c

${OBJECTDIR}/src/perf-gear.o: src/perf-gear.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/perf-gear.o src/perf-gear.c

${OBJECTDIR}/src/pg-utils.o: src/pg-utils.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pg-utils.o src/pg-utils.c

${OBJECTDIR}/src/queue.o: src/queue.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/queue.o src/queue.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/collector-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/dispatcher-test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} -lcunit 

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


${TESTDIR}/tests/collector-test.o: tests/collector-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/collector-test.o tests/collector-test.c


${TESTDIR}/tests/dispatcher-test.o: tests/dispatcher-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/dispatcher-test.o tests/dispatcher-test.c


${TESTDIR}/tests/linked-list-test.o: tests/linked-list-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/linked-list-test.o tests/linked-list-test.c


${TESTDIR}/tests/measurement2json-test.o: tests/measurement2json-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/measurement2json-test.o tests/measurement2json-test.c


${TESTDIR}/tests/perf-gear-test.o: tests/perf-gear-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/perf-gear-test.o tests/perf-gear-test.c


${TESTDIR}/tests/pg-utils-test.o: tests/pg-utils-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pg-utils-test.o tests/pg-utils-test.c


${TESTDIR}/tests/queue-test.o: tests/queue-test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/queue-test.o tests/queue-test.c


${OBJECTDIR}/src/collector_nomain.o: ${OBJECTDIR}/src/collector.o src/collector.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/collector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/collector_nomain.o src/collector.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/collector.o ${OBJECTDIR}/src/collector_nomain.o;\
	fi

${OBJECTDIR}/src/dispatcher_nomain.o: ${OBJECTDIR}/src/dispatcher.o src/dispatcher.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/dispatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/dispatcher_nomain.o src/dispatcher.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/dispatcher.o ${OBJECTDIR}/src/dispatcher_nomain.o;\
	fi

${OBJECTDIR}/src/linked-list_nomain.o: ${OBJECTDIR}/src/linked-list.o src/linked-list.c 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/linked-list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/linked-list_nomain.o src/linked-list.c;\
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
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/measurement2json_nomain.o src/measurement2json.c;\
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
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/perf-gear_nomain.o src/perf-gear.c;\
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
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pg-utils_nomain.o src/pg-utils.c;\
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
	    $(COMPILE.c) -O2 -Werror -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/queue_nomain.o src/queue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/src/queue.o ${OBJECTDIR}/src/queue_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
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
