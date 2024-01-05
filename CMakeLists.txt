cmake_minimum_required(VERSION 3.16)

project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(DEPS_BUILD)
SET(FETCHCONTENT_TRY_FIND_PACKAGE_MODE NEVER)
else()
SET(FETCHCONTENT_TRY_FIND_PACKAGE_MODE ALWAYS)
endif()
set(FETCHCONTENT_QUIET OFF)

Include(FetchContent)

FetchContent_Declare(
  SDBusCpp
  GIT_REPOSITORY https://github.com/Kistler-Group/sdbus-cpp
  GIT_TAG        v1.2.0
# Figure out how to make it work
  FIND_PACKAGE_ARGS NAMES SDBusCpp sdbus-c++
#  OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(SDBusCpp)

# First, find sdbus-c++

set(KF5_MIN_VERSION "5.102.0")
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMQtDeclareLoggingCategory)

set(PKG_QT Qt${QT_MAJOR_VERSION})

find_package(${PKG_QT} REQUIRED COMPONENTS Core Widgets Quick  Gui QuickControls2)

find_package(KF5 REQUIRED COMPONENTS CoreAddons I18n Kirigami2)


find_package(PkgConfig REQUIRED )
pkg_check_modules(GStreamer REQUIRED IMPORTED_TARGET gstreamer-1.0)
pkg_check_modules(libva REQUIRED IMPORTED_TARGET libva)
pkg_check_modules(PipeWire REQUIRED IMPORTED_TARGET libpipewire-0.3)

# find_package(KF5Kirigami2 REQUIRED)


find_package(Threads REQUIRED)


#file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.hpp)
#kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
#kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

kde_enable_exceptions()


add_subdirectory(src)
