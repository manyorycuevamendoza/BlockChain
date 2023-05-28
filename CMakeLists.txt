cmake_minimum_required(VERSION 3.12)
project(Blockchain)

set(CMAKE_CXX_STANDARD 11)

# Agrega tus archivos fuente (.cpp) aquí
set(SOURCES
        main.cpp
        arbolavl.cpp
        # ...
        )

# Agrega tus archivos de encabezado (.h) aquí
set(HEADERS
        avl.h
        blockchain.h
        chaining.h
        lectura.h
        node_blockchain.h
        SHA256.h
        # ...
        )

# Configuración del ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
