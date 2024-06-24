#!/bin/bash

if [ -z "${CC}" -o -z "${CXX}" ]; then
    echo "ERROR: Compilers are not provided"
    exit 1
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_DIR=$( dirname ${SCRIPT_DIR} )
if [ -z "${BUILD_DIR}" ]; then
    BUILD_DIR="${ROOT_DIR}/build.${CC}"
fi

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

if [ -z "${COMMON_INSTALL_DIR}" ]; then
    COMMON_INSTALL_DIR=install
fi

if [ -z "${COMMON_BUILD_TYPE}" ]; then
    COMMON_BUILD_TYPE=Debug
fi

cmake .. -DCMAKE_INSTALL_PREFIX=${COMMON_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${COMMON_BUILD_TYPE} -DOPT_USE_SANITIZERS=ON \
    -DOPT_USE_CCACHE=ON "$@"
