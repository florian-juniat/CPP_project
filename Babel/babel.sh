#!/bin/bash

function    print_usage {
    printf "Usage: ./build.sh [COMMAND]

COMMAND:
    -i, --install   install conan + remote repo + all dependencies (qt|portaudio|opus), create build repo and build your project
                    (may take few minutes)
    -cm, --cmake    create cmake
    -cl, --clean    clean all cmake files (must be use before push)\r\n"
}

function    p_error {
    echo >&2 $@
}

function    install {
    local TMP=`which conan`
    local QT=""
    if [[ -z $TMP ]]; then
        pip3 install conan
    fi
    conan remote add conan https://conan.bintray.com
    conan remote add conan-center https://api.bintray.com/conan/conan/conan-center
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
    printf "Do you want to build qt from source ? [y/n] "
    read RESP
    if [[ $RESP == "y" ]]; then
        QT="--build qt"
    fi
    TMP=`ls | grep build`
    if [[ -n $TMP ]]; then
        printf "Do you want to override your build ? [y/n] "
        read RESP
        if [[ $RESP == "y" ]]; then
            rm -rf build && mkdir build && cd build && conan install .. $QT && cd ..
        fi
    else
        mkdir build && cd build && conan install .. $QT && cd ..
    fi
}

function _cmake {
    cd build && cmake .. -G "Unix Makefiles" && cmake -build . && cd ..
}

function clean {
    cd build && rm -rf CMakeFiles bin CMakeCache.txt cmake_install.cmake Makefile babel_client_autogen server graph && cd ..
}

function    check_args {
    if [[ $# != 1 ]]; then
        print_usage
        exit 84
    fi
    case $1 in
        -i|--install)
            install
            ;;
        -cm|--cmake)
            _cmake
            ;;
        -cl|--clean)
            clean
            ;;
        -h|--help)
            print_usage
            ;;
        *)
            p_error "build.sh: command not found: \"$1\""
            p_error "Try './build.sh -h'  for more information."
            exit 1
    esac
    exit 0
}

function    main {
    check_args $@
}

main    $@
