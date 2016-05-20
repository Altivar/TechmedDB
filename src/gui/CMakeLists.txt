
FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtXml QtSql)
INCLUDE(${QT_USE_FILE})

# set the target libraries
SET(TARGET_LIBS ${TARGET_LIBS} ${QT_LIBRARIES})


# include the current binary dir for the generated header files (UI)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

include_directories(.)
file(GLOB_RECURSE TechmedDBSrcs ./*.cpp)
file(GLOB_RECURSE TechmedDBHeaders ./*.h)
file(GLOB_RECURSE TechmedDBUI ./*.ui)


QT4_WRAP_UI(TDB_UISrcs ${TechmedDBUI})
QT4_WRAP_CPP(TDB_MOCSrcs ${TechmedDBHeaders})
QT4_ADD_RESOURCES(TDB_ResourceSrcs ${TechMedDBResources})

SOURCE_GROUP("Resources" FILES
  ${TechmedDBUI}
  ${TechMedDBResources}
  ${EXE_ICON}
)

SOURCE_GROUP("Generated" FILES
  ${TDB_UISrcs}
  ${TDB_MOCSrcs}
  ${TDB_ResourceSrcs}
  ${TDB_RCS_SOURCES}
)


ADD_DEFINITIONS(-DQT_GUI_LIBS -DQT_CORE_LIB -DQT_XML_LIB -DQT3_SUPPORT)
SET_SOURCE_FILES_PROPERTIES(${TechmedDBSrcs} PROPERTIES
                            OBJECT_DEPENDS "${TDB_UISrcs}")

# It's nice to have the ui in the windows project file... just double click on it
# and designer comes up on that ui file :)
IF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
  SET (TechmedDBSrcs ${TechmedDBSrcs} ${TechmedDBUI})
ENDIF (${CMAKE_BUILD_TOOL} MATCHES "msdev")
IF (${CMAKE_BUILD_TOOL} MATCHES "devenv")
  SET (TechmedDBSrcs ${TechmedDBSrcs} ${TechmedDBUI})
ENDIF (${CMAKE_BUILD_TOOL} MATCHES "devenv")

# copy resources next to exe
file(COPY ${CMAKE_SOURCE_DIR}/src/gui/images DESTINATION ${PROJECT_BINARY_DIR}/src/gui/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/src/gui/images DESTINATION ${PROJECT_BINARY_DIR}/src/gui/Release)
# copy resources for accessing from solution
file(COPY ${CMAKE_SOURCE_DIR}/src/gui/images DESTINATION ${PROJECT_BINARY_DIR}/src/gui)
# copy database next to exe
file(COPY ${CMAKE_SOURCE_DIR}/src/db/TechmedDB.db DESTINATION ${PROJECT_BINARY_DIR}/src/gui/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/src/db/TechmedDB.db DESTINATION ${PROJECT_BINARY_DIR}/src/gui/Release)
# copy database for accessing from solution
file(COPY ${CMAKE_SOURCE_DIR}/src/db/TechmedDB.db DESTINATION ${PROJECT_BINARY_DIR}/src/gui)


ADD_EXECUTABLE(TechMedDB MACOSX_BUNDLE ${TechmedDBSrcs} ${TDB_UISrcs} ${TDB_MOCSrcs} ${TDB_ResourceSrcs})
#link_libraries(${VTK_LIBRARY_DIRS})
TARGET_LINK_LIBRARIES(TechMedDB TDB ${TARGET_LIBS})
SET_TARGET_PROPERTIES(TechMedDB PROPERTIES COMPILE_FLAGS "${SHARED_FLAGS} ${TECHMED_flags}")
