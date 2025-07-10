cmake_minimum_required(VERSION 3.16)

project(Zgame LANGUAGES CXX)

# Padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios de include
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/include/SDL2)

# Diretórios de código-fonte
file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/include/*.h
    ${PROJECT_SOURCE_DIR}/assets/*
)

# Link com bibliotecas SDL2 (simples)
link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# Executável
add_executable(Zgame ${SOURCE_FILES})

# Instalação
include(GNUInstallDirs)
install(TARGETS Zgame
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Opcional: copiar assets junto da instalação
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/
    DESTINATION ${CMAKE_INSTALL_BINDIR}/assets
    FILES_MATCHING PATTERN "*.*"
)
