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
CCC=gcc
CXX=gcc
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/73483906/primitives.o \
	${OBJECTDIR}/_ext/73483906/md2Loader.o \
	${OBJECTDIR}/_ext/2057539350/normalTest.o \
	${OBJECTDIR}/_ext/2057539350/bspTest.o \
	${OBJECTDIR}/_ext/2057539350/matrixTest.o \
	${OBJECTDIR}/_ext/2057539350/backfaceCullingTest.o \
	${OBJECTDIR}/_ext/73483906/main.o \
	${OBJECTDIR}/_ext/2057539350/polygonTest.o \
	${OBJECTDIR}/_ext/73483906/matrix.o \
	${OBJECTDIR}/_ext/2057539350/testMain.o \
	${OBJECTDIR}/_ext/2057539350/md2ImportTest.o \
	${OBJECTDIR}/_ext/2057539350/meshTest.o \
	${OBJECTDIR}/_ext/73483906/bspTree.o \
	${OBJECTDIR}/_ext/73483906/scene.o \
	${OBJECTDIR}/_ext/2057539350/solidDrawTest.o \
	${OBJECTDIR}/_ext/73483906/codeSnippets.o \
	${OBJECTDIR}/_ext/2057539350/mathematicsTest.o \
	${OBJECTDIR}/_ext/73483906/draw.o \
	${OBJECTDIR}/_ext/73483906/mesh.o \
	${OBJECTDIR}/_ext/73483906/mathematics.o \
	${OBJECTDIR}/_ext/2057539350/sceneTest.o \
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
LDLIBSOPTIONS=-lSDL -lm

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dummyengine ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/73483906/primitives.o: /home/topias/TiRa/TiRa/DummyEngine/primitives.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/primitives.o /home/topias/TiRa/TiRa/DummyEngine/primitives.c

${OBJECTDIR}/_ext/73483906/md2Loader.o: /home/topias/TiRa/TiRa/DummyEngine/md2Loader.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/md2Loader.o /home/topias/TiRa/TiRa/DummyEngine/md2Loader.c

${OBJECTDIR}/_ext/2057539350/normalTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/normalTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/normalTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/normalTest.c

${OBJECTDIR}/_ext/2057539350/bspTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/bspTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/bspTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/bspTest.c

${OBJECTDIR}/_ext/2057539350/matrixTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/matrixTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/matrixTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/matrixTest.c

${OBJECTDIR}/_ext/2057539350/backfaceCullingTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/backfaceCullingTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/backfaceCullingTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/backfaceCullingTest.c

${OBJECTDIR}/_ext/73483906/main.o: /home/topias/TiRa/TiRa/DummyEngine/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/main.o /home/topias/TiRa/TiRa/DummyEngine/main.c

${OBJECTDIR}/_ext/2057539350/polygonTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/polygonTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/polygonTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/polygonTest.c

${OBJECTDIR}/_ext/73483906/matrix.o: /home/topias/TiRa/TiRa/DummyEngine/matrix.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/matrix.o /home/topias/TiRa/TiRa/DummyEngine/matrix.c

${OBJECTDIR}/_ext/2057539350/testMain.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/testMain.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/testMain.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/testMain.c

${OBJECTDIR}/_ext/2057539350/md2ImportTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/md2ImportTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/md2ImportTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/md2ImportTest.c

${OBJECTDIR}/_ext/2057539350/meshTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/meshTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/meshTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/meshTest.c

${OBJECTDIR}/_ext/73483906/bspTree.o: /home/topias/TiRa/TiRa/DummyEngine/bspTree.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/bspTree.o /home/topias/TiRa/TiRa/DummyEngine/bspTree.c

${OBJECTDIR}/_ext/73483906/scene.o: /home/topias/TiRa/TiRa/DummyEngine/scene.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/scene.o /home/topias/TiRa/TiRa/DummyEngine/scene.c

${OBJECTDIR}/_ext/2057539350/solidDrawTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/solidDrawTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/solidDrawTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/solidDrawTest.c

${OBJECTDIR}/_ext/73483906/codeSnippets.o: /home/topias/TiRa/TiRa/DummyEngine/codeSnippets.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/codeSnippets.o /home/topias/TiRa/TiRa/DummyEngine/codeSnippets.c

${OBJECTDIR}/_ext/2057539350/mathematicsTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/mathematicsTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/mathematicsTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/mathematicsTest.c

${OBJECTDIR}/_ext/73483906/draw.o: /home/topias/TiRa/TiRa/DummyEngine/draw.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/draw.o /home/topias/TiRa/TiRa/DummyEngine/draw.c

${OBJECTDIR}/_ext/73483906/mesh.o: /home/topias/TiRa/TiRa/DummyEngine/mesh.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/mesh.o /home/topias/TiRa/TiRa/DummyEngine/mesh.c

${OBJECTDIR}/_ext/73483906/mathematics.o: /home/topias/TiRa/TiRa/DummyEngine/mathematics.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/mathematics.o /home/topias/TiRa/TiRa/DummyEngine/mathematics.c

${OBJECTDIR}/_ext/2057539350/sceneTest.o: /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/sceneTest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2057539350
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2057539350/sceneTest.o /home/topias/TiRa/TiRa/DummyEngine/Test\ Files/sceneTest.c

${OBJECTDIR}/_ext/73483906/sdltest.o: /home/topias/TiRa/TiRa/DummyEngine/sdltest.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/73483906
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/73483906/sdltest.o /home/topias/TiRa/TiRa/DummyEngine/sdltest.c

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
