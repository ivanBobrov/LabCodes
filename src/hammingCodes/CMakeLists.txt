set(LAB_SOURCE
    main.cpp
    HammingCodesLab.cpp
    HammingLabWidget.cpp
    HammingLabProcessor.cpp
    HammingLabResult.cpp
    HammingLabEventEmitter.cpp
)

if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	
	if (WIN32)
		set(GUI_TYPE WIN32)
	endif()
    add_executable(hammingCodes ${GUI_TYPE} ${LAB_SOURCE})
    target_link_libraries(hammingCodes codesLib ${Boost_LIBRARIES})
	#if (WIN32)
	#	target_link_libraries(hammingCodes Qt5::WinMain)
	#endif()
	
	target_compile_features(hammingCodes PUBLIC cxx_strong_enums)
    qt5_use_modules(hammingCodes Widgets)
else()
    message(FATAL_ERROR "Can't locate Boost library")
endif()

