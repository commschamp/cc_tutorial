#!/bin/bash

# Input
# BUILD_DIR - Main build directory
# CC - Main C compiler
# CXX - Main C++ compiler
# CC_COMMSDSL - C compiler for commsdsl
# CXX_COMMSDSL - C++ compiler for commsdsl
# EXTERNALS_DIR - (Optional) Directory where externals need to be located
# COMMS_REPO - (Optional) Repository of the COMMS library
# COMMS_TAG - (Optional) Tag of the COMMS library
# COMMSDSL_REPO - (Optional) Repository of the commsdsl code generators
# COMMSDSL_TAG - (Optional) Tag of the commdsl
# COMMON_INSTALL_DIR - (Optional) Common directory to perform installations
# COMMON_BUILD_TYPE - (Optional) CMake build type
# COMMON_CXX_STANDARD - (Optional) CMake C++ standard

#####################################

if [ -z "${BUILD_DIR}" ]; then
    echo "BUILD_DIR hasn't been specified"
    exit 1
fi

if [ -z "${EXTERNALS_DIR}" ]; then
    EXTERNALS_DIR=${BUILD_DIR}/externals
fi

if [ -z "${COMMS_REPO}" ]; then
    COMMS_REPO=https://github.com/commschamp/comms.git
fi

if [ -z "${COMMS_TAG}" ]; then
    COMMS_TAG=master
fi

if [ -z "${COMMSDSL_REPO}" ]; then
    COMMSDSL_REPO=https://github.com/commschamp/commsdsl.git
fi

if [ -z "${COMMSDSL_TAG}" ]; then
    COMMSDSL_TAG=master
fi

if [ -z "${COMMON_BUILD_TYPE}" ]; then
    COMMON_BUILD_TYPE=Debug
fi

if [ -z "${CC_COMMSDSL}" ]; then
    CC_COMMSDSL=${CC}
fi

if [ -z "${CXX_COMMSDSL}" ]; then
    CXX_COMMSDSL=${CXX}
fi

COMMS_SRC_DIR=${EXTERNALS_DIR}/comms
COMMS_BUILD_DIR=${BUILD_DIR}/externals/comms/build
COMMS_INSTALL_DIR=${COMMS_BUILD_DIR}/install
if [ -n "${COMMON_INSTALL_DIR}" ]; then
    COMMS_INSTALL_DIR=${COMMON_INSTALL_DIR}
fi

COMMSDSL_SRC_DIR=${EXTERNALS_DIR}/commsdsl
COMMSDSL_BUILD_DIR=${BUILD_DIR}/externals/commsdsl/build
COMMSDSL_INSTALL_DIR=${COMMSDSL_BUILD_DIR}/install
if [ -n "${COMMON_INSTALL_DIR}" ]; then
    COMMSDSL_INSTALL_DIR=${COMMON_INSTALL_DIR}
fi

procs=$(nproc)
if [ -n "${procs}" ]; then
    procs_param="-- -j${procs}"
fi

#####################################

function build_comms() {
    if [ -e ${COMMS_SRC_DIR}/.git ]; then
        echo "Updating COMMS library..."
        cd ${COMMS_SRC_DIR}
        git fetch --all
        git checkout .
        git checkout ${COMMS_TAG}
        git pull --all
    else
        echo "Cloning COMMS library..."
        mkdir -p ${EXTERNALS_DIR}
        git clone -b ${COMMS_TAG} ${COMMS_REPO} ${COMMS_SRC_DIR}
    fi

    echo "Building COMMS library..."
    mkdir -p ${COMMS_BUILD_DIR}
    cmake -S ${COMMS_SRC_DIR} -B ${COMMS_BUILD_DIR} -DCMAKE_INSTALL_PREFIX=${COMMS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${COMMON_BUILD_TYPE} -DCMAKE_CXX_STANDARD=${COMMON_CXX_STANDARD}
    cmake --build ${COMMS_BUILD_DIR} --config ${COMMON_BUILD_TYPE} --target install ${procs_param}
}

function build_commsdsl() {
    if [ -e ${COMMSDSL_SRC_DIR}/.git ]; then
        echo "Updating commsdsl..."
        cd ${COMMSDSL_SRC_DIR}
        git fetch --all
        git checkout .
        git checkout ${COMMSDSL_TAG}
        git pull --all
    else
        echo "Cloning commsdsl ..."
        mkdir -p ${EXTERNALS_DIR}
        git clone -b ${COMMSDSL_TAG} ${COMMSDSL_REPO} ${COMMSDSL_SRC_DIR}
    fi

    echo "Building commsdsl ..."
    mkdir -p ${COMMSDSL_BUILD_DIR}
    CC=${CC_COMMSDSL} CXX=${CXX_COMMSDSL} cmake -S ${COMMSDSL_SRC_DIR} -B ${COMMSDSL_BUILD_DIR} \
        -DCMAKE_INSTALL_PREFIX=${COMMSDSL_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${COMMON_BUILD_TYPE} \
        -DCOMMSDSL_INSTALL_LIBRARY=OFF 
    cmake --build ${COMMSDSL_BUILD_DIR} --config ${COMMON_BUILD_TYPE} --target install ${procs_param}
}

set -e
export VERBOSE=1
build_comms
build_commsdsl



