cmake_minimum_required(VERSION 3.10)

project(adwaita-tab-view)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wno-unused-parameter")

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(LIBADWAITA REQUIRED IMPORTED_TARGET libadwaita-1)

add_custom_command(
        OUTPUT resources.c resources.h
        COMMAND glib-compile-resources resources.xml --generate-source --target=resources.c
        COMMAND glib-compile-resources resources.xml --generate-header --target=resources.h
        DEPENDS resources.xml
)

add_executable(${PROJECT_NAME}
        main.c
        adw-tab-view-demo-window.c
        adw-tab-view-demo-window.h
        adw-tab-view-demo-page.c
        adw-tab-view-demo-page.h
        resources.c
        resources.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        PkgConfig::GTK4
        PkgConfig::LIBADWAITA
)
