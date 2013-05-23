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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/73483906/testMain.o \
	${OBJECTDIR}/_ext/73483906/meshTest.o \
	${OBJECTDIR}/_ext/73483906/main.o \
	${OBJECTDIR}/_ext/73483906/matrix.o \
	${OBJECTDIR}/_ext/73483906/renderTest.o \
	${OBJECTDIR}/_ext/73483906/matrixTest.o \
	${OBJECTDIR}/_ext/73483906/codeSnippets.o \
	${OBJECTDIR}/_ext/73483906/mesh.o \
	${OBJECTDIR}/_ext/73483906/draw.o \
	${OBJECTDIR}/_ext/73483906/sdltest.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/73483906/testMain.o: /home/topias/TiRa/TiRa/DummyEngine/testMain.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/testMain.o /home/topias/TiRa/TiRa/DummyEngine/testMain.c

${OBJECTDIR}/_ext/73483906/meshTest.o: /home/topias/TiRa/TiRa/DummyEngine/meshTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/meshTest.o /home/topias/TiRa/TiRa/DummyEngine/meshTest.c

${OBJECTDIR}/_ext/73483906/main.o: /home/topias/TiRa/TiRa/DummyEngine/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/main.o /home/topias/TiRa/TiRa/DummyEngine/main.c

${OBJECTDIR}/_ext/73483906/matrix.o: /home/topias/TiRa/TiRa/DummyEngine/matrix.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/matrix.o /home/topias/TiRa/TiRa/DummyEngine/matrix.c

${OBJECTDIR}/_ext/73483906/renderTest.o: /home/topias/TiRa/TiRa/DummyEngine/renderTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/renderTest.o /home/topias/TiRa/TiRa/DummyEngine/renderTest.c

${OBJECTDIR}/_ext/73483906/matrixTest.o: /home/topias/TiRa/TiRa/DummyEngine/matrixTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/matrixTest.o /home/topias/TiRa/TiRa/DummyEngine/matrixTest.c

${OBJECTDIR}/_ext/73483906/codeSnippets.o: /home/topias/TiRa/TiRa/DummyEngine/codeSnippets.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/codeSnippets.o /home/topias/TiRa/TiRa/DummyEngine/codeSnippets.c

${OBJECTDIR}/_ext/73483906/mesh.o: /home/topias/TiRa/TiRa/DummyEngine/mesh.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/mesh.o /home/topias/TiRa/TiRa/DummyEngine/mesh.c

${OBJECTDIR}/_ext/73483906/draw.o: /home/topias/TiRa/TiRa/DummyEngine/draw.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/draw.o /home/topias/TiRa/TiRa/DummyEngine/draw.c

${OBJECTDIR}/_ext/73483906/sdltest.o: /home/topias/TiRa/TiRa/DummyEngine/sdltest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/sdltest.o /home/topias/TiRa/TiRa/DummyEngine/sdltest.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
