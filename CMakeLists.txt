cmake_minimum_required(VERSION 3.26)
project(ShunscomTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#[[
set(CMAKE_PREFIX_PATH "F:/Qt/6.5.3/mingw_64")]]

#[[
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
]]


set(CMAKE_PREFIX_PATH "F:/ShunscomTest/vcpkg_installed/x64-windows")




find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)

include_directories(
        ./${libusb_INCLUDE_DIRS}
)



add_executable(ShunscomTest ./main/main.cpp
        createlib/iolib/USBIO.cpp
        createlib/iolib/SerialIO.cpp
        createlib/iolib/SerialIO.h
        createlib/iolib/FileIO.cpp
        createlib/iolib/FileIO.h
        createlib/utils/charutil.h
        createlib/utils/xmlhelp.h
        createlib/utils/tinyxml2.cpp
        createlib/utils/tinyxml2.h
        test/test.h
        createlib/iolib/QualCommDMSerial.cpp
        createlib/iolib/QualCommDMSerial.h
        createlib/utils/xmlhelp.cpp
        createlib/utils/charutil.cpp
        createlib/utils/logger.cpp
        createlib/utils/logger.h
        createlib/utils/qualcommcommand.h
        createlib/utils/numberhelp.cpp
        createlib/utils/numberhelp.h
        createlib/iolib/hdlc.cpp
        createlib/iolib/hdlc.h
        createlib/iolib/hdlc.cpp

)
target_link_libraries(ShunscomTest
#[[        Qt::Core
        Qt::Gui
        Qt::Widgets]]
        PkgConfig::libusb
)


#[[
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
]]
