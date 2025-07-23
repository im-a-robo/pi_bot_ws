#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "motor_driver::motor_driver" for configuration ""
set_property(TARGET motor_driver::motor_driver APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(motor_driver::motor_driver PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmotor_driver.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS motor_driver::motor_driver )
list(APPEND _IMPORT_CHECK_FILES_FOR_motor_driver::motor_driver "${_IMPORT_PREFIX}/lib/libmotor_driver.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
