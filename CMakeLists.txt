
cmake_minimum_required(VERSION 3.14)

project(HTMLDOM  LANGUAGES CXX)


option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(LTO)

include(Warnings)

find_lto(CXX)


set(SOURCES         
 

  src/nodeList.cpp 
  src/element.cpp
  src/node.cpp 
  src/utils.cpp
  src/document.cpp
  src/attribute.cpp
  src/text.cpp
  src/characterdata.cpp
   
   
    
)
set(TESTFILES        
    tests/main.cpp
    tests/document.cpp
    tests/element.include(CPackPackageMaker)
)
set(LIBRARY_NAME htmldom)  


add_library(${LIBRARY_NAME} OBJECT ${SOURCES})


target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)




target_link_libraries(${LIBRARY_NAME} PUBLIC doctest)


target_set_warnings(${LIBRARY_NAME} ENABLE ALL AS_ERROR ALL DISABLE Annoying)


add_executable(main examples/example1.cpp)   
target_link_libraries(main PRIVATE ${LIBRARY_NAME}) 
target_set_warnings(main ENABLE ALL AS_ERROR ALL DISABLE Annoying) 
target_enable_lto(main optimized) 

set_target_properties(
    ${LIBRARY_NAME} main
      PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)


add_subdirectory(tests)
