set(LAB_SOURCE
        main.cpp
        MainWindow.cpp
        AboutWindow.cpp
        CyclicCodesWidget.cpp
        CyclicCodesLab.cpp
        LabTaskRunner.cpp
        CyclicLabResult.cpp
        CyclicLabTask.cpp
        CyclicPolynomialLabel.cpp
        BarChartWidget.cpp
        )

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    if (WIN32)
        set(GUI_TYPE WIN32)
    endif()

    add_executable(cyclicCodes ${GUI_TYPE} ${LAB_SOURCE})
    target_link_libraries(cyclicCodes codesLib ${Boost_LIBRARIES})

    target_compile_features(cyclicCodes PUBLIC cxx_strong_enums)
    qt5_use_modules(cyclicCodes Widgets)
else()
    message(FATAL_ERROR "Can't locate Boost library")
endif()