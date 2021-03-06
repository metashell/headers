cmake_minimum_required(VERSION 2.6)
project(headers)
set(CMAKE_PROJECT_NAME headers)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

install(DIRECTORY headers DESTINATION include)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()

# Debian package
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  include(InstallRequiredSystemLibraries)
   
  set(CPACK_SET_DESTDIR "on")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
  set(CPACK_GENERATOR "DEB")
   
  set(CPACK_PACKAGE_DESCRIPTION "Headers")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Headers of multiple versions of libraries")
  set(CPACK_PACKAGE_VENDOR "Abel Sinkovics")
  set(CPACK_PACKAGE_CONTACT "abel@sinkovics.hu")
  set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")

  set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
  set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
  set(CPACK_DEBIAN_ARCHITECTURE "all") # Header-only
   
  set(CPACK_COMPONENTS_ALL headers)
  include(CPack)
   
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")



