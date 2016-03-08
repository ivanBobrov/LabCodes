set(CODES_SOURCES
    Message.cpp
    SimplePolynomial.cpp
    CodeConverter.cpp
    EnvironmentImitator.cpp
    )

add_library(codesLib ${CODES_SOURCES})
target_include_directories(codesLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(codesLib PUBLIC cxx_strong_enums)