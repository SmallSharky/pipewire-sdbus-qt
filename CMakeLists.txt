cmake_minimum_required(VERSION 3.16)

project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

find_package(${PKG_QT} REQUIRED COMPONENTS Core Widgets Quick)

find_package(KF5 REQUIRED COMPONENTS CoreAddons I18n)

find_package(sdbus-c++ REQUIRED)
find_package(Threads REQUIRED)


file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.hpp)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

kde_enable_exceptions()


add_subdirectory(src)
