set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

project (peg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

# boost
# set(BOOST_ROOT /specific/boost/path)
find_package(Boost COMPONENTS system thread chrono date_time atomic REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#crow and nt partition
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/partition)

# antlr3
include_directories(${PROJECT_SOURCE_DIR}/queryDecompose/tools/libantlr3c-3.4)
include_directories(${PROJECT_SOURCE_DIR}/queryDecompose/tools/libantlr3c-3.4/include)
link_directories(${PROJECT_SOURCE_DIR}/queryDecompose/lib)

aux_source_directory(gStoreAPI gstoreapiSRC)
aux_source_directory(queryDecompose/Parser parserSRC)
aux_source_directory(queryDecompose/Query querySRC)
aux_source_directory(queryDecompose/Util utilSRC)
aux_source_directory(util util)
aux_source_directory(joiner joinerSRC)
aux_source_directory(dbUtil dbUtilSRC)
aux_source_directory(tojson jsonSRC)
aux_source_directory(sendcapt sendcaptSRC)
aux_source_directory(handler handlerSRC)


# server
add_executable(server peg_server.cpp ${gstoreapiSRC} ${parserSRC} ${querySRC} ${sendcaptSRC} ${utilSRC} ${joinerSRC} ${util} ${handlerSRC} ${jsonSRC} ${dbUtilSRC})
target_link_libraries(server pthread)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server curl)
target_link_libraries(server libantlr.a)
target_link_libraries(server mysqlclient)



#add_executable(PEG_check checkdb.cpp)
#target_link_libraries(PEG_check mysqlclient)


# 谁需要数据库给谁。
# target_link_libraries(${PROJECT_NAME} mysqlclient)

