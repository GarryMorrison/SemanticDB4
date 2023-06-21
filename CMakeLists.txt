cmake_minimum_required(VERSION 3.10)
project(SDB4)

set(CMAKE_CXX_STANDARD 17)

if (USE_GPROF)
    message("Configuring for gprof")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()

# find build requirements
FIND_PACKAGE(BISON 3.3 REQUIRED)
FIND_PACKAGE(FLEX)

## INCLUDES
# include root source directory for includes search
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
# include binary build directory for includes search
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})



## SDB CORE
# Parser: generated bison/flex outputs for Parser
BISON_TARGET(Parser src/core/Parser/Parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(Lexer src/core/Parser/Scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.h)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Parser: set parser header and source files explicitly to avoid any generated bison/flex outputs
set(Parser_SRC "src/core/Parser/Driver.h" "src/core/Parser/Driver.cpp" "src/core/Parser/Scanner.h")

# collect all files ending in .h and .cpp
file(GLOB CompoundConstant_SRC CONFIGURE_DEPENDS "src/core/CompoundConstant/*.h" "src/core/CompoundConstant/*.cpp")
file(GLOB Context_SRC CONFIGURE_DEPENDS "src/core/Context/*.h" "src/core/Context/*.cpp")
file(GLOB Function_SRC CONFIGURE_DEPENDS "src/core/Function/*.h" "src/core/Function/*.cpp")
file(GLOB FunctionOperatorMap_SRC CONFIGURE_DEPENDS "src/core/FunctionOperatorMap/*.h" "src/core/FunctionOperatorMap/*.cpp")
file(GLOB KetMap_SRC CONFIGURE_DEPENDS "src/core/KetMap/*.h" "src/core/KetMap/*.cpp")
file(GLOB Operator_SRC CONFIGURE_DEPENDS "src/core/Operator/*.h" "src/core/Operator/*.cpp")
file(GLOB OperatorLibrary_SRC CONFIGURE_DEPENDS "src/core/OperatorLibrary/*.h" "src/core/OperatorLibrary/*.cpp")
file(GLOB OperatorUsageMap_SRC CONFIGURE_DEPENDS "src/core/OperatorUsageMap/*.h" "src/core/OperatorUsageMap/*.cpp")
file(GLOB Sequence_SRC CONFIGURE_DEPENDS "src/core/Sequence/*.h" "src/core/Sequence/*.cpp")

# SDB CORE library
set(CORE_SOURCE_FILES
     ${Parser_SRC}
     ${BISON_Parser_OUTPUTS}
     ${FLEX_Lexer_OUTPUTS}
     ${CompoundConstant_SRC}
     ${Context_SRC}
     ${Function_SRC}
     ${FunctionOperatorMap_SRC}
     ${KetMap_SRC}
     ${Operator_SRC}
     ${OperatorLibrary_SRC}
     ${OperatorUsageMap_SRC}
     ${Sequence_SRC}
)
add_library(SDB4_core STATIC src/core/SDB_core.h ${CORE_SOURCE_FILES})

if(BUILD_GUI)
    message("GUI build")

    # include wxWidgets:
    set(wxWidgets_USE_LIBS)
    find_package(wxWidgets REQUIRED COMPONENTS all)
    include(${wxWidgets_USE_FILE})
    include_directories(${wxWidgets_INCLUDE_DIRS})

    # collect GUI .h and .cpp files:
    file(GLOB GUIInterface_SRC CONFIGURE_DEPENDS "src/GUI/Interface/*.h" "src/GUI/Interface/*.cpp")
    file(GLOB GUIAssociated_SRC CONFIGURE_DEPENDS "src/GUI/Associated/*.h" "src/GUI/Associated/*.cpp")
    file(GLOB GUIOperatorLibrary_SRC CONFIGURE_DEPENDS "src/GUI/OperatorLibrary/*.h" "src/GUI/OperatorLibrary/*.cpp")
    file(GLOB GUILexerColorMap_SRC CONFIGURE_DEPENDS "src/GUI/LexerColorMap/*.h" "src/GUI/LexerColorMap/*.cpp")

    # SDB GUI code
    set(GUI_SOURCE_FILES
        ${GUIInterface_SRC}
        ${GUIAssociated_SRC}
        ${GUIOperatorLibrary_SRC}
        ${GUILexerColorMap_SRC}
    )

    # BUILD TARGETS
    add_executable(SDB4_GUI src/GUI/SDB_GUI.cpp src/GUI/SDB_GUI.h ${GUI_SOURCE_FILES})
    target_link_libraries(SDB4_GUI SDB4_core ${wxWidgets_LIBRARIES})
endif()


if(BUILD_CLI)
    message("CLI build")
    
    # include 3rd party headers for includes search
    INCLUDE_DIRECTORIES(src/CLI/tclap/)
    
    # collect GUI .h and .cpp files:
    file(GLOB DocsGenerator_SRC CONFIGURE_DEPENDS "src/CLI/DocsGenerator/*.h" "src/CLI/DocsGenerator/*.cpp")
    
    # SDB CLI code
    set(CLI_SOURCE_FILES
        ${DocsGenerator_SRC}
    )
    
    # CLI target binary
    add_executable(SDB4_CLI src/CLI/main.cpp src/CLI/SDB_CLI.h ${CLI_SOURCE_FILES})
    target_link_libraries(SDB4_CLI SDB4_core)
endif()



# test main binary
# add_executable(test_main src/test_main.cpp src/SDB3_header.h)
# target_link_libraries(test_main sdb_core)

# test parser binary
# add_executable(test_parser src/test_parser_main.cpp src/SDB3_header.h)
# target_link_libraries(test_parser sdb_core)

