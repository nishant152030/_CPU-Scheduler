cmake_minimum_required(VERSION 3.28)
project(main)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/crow)
include_directories(include/crow/middlewares)

add_executable(acm
        include/crow/middlewares/cookie_parser.h
        include/crow/middlewares/cors.h
        include/crow/middlewares/session.h
        include/crow/middlewares/utf-8.h
        include/crow/app.h
        include/crow/ci_map.h
        include/crow/common.h
        include/crow/compression.h
        include/crow/http_connection.h
        include/crow/http_parser_merged.h
        include/crow/http_request.h
        include/crow/http_response.h
        include/crow/http_server.h
        include/crow/json.h
        include/crow/logging.h
        include/crow/middleware.h
        include/crow/middleware_context.h
        include/crow/mime_types.h
        include/crow/multipart.h
        include/crow/mustache.h
        include/crow/parser.h
        include/crow/query_string.h
        include/crow/returnable.h
        include/crow/routing.h
        include/crow/settings.h
        include/crow/socket_adaptors.h
        include/crow/task_timer.h
        include/crow/TinySHA1.hpp
        include/crow/utility.h
        include/crow/version.h
        include/crow/websocket.h
        include/crow.h
        main.cpp
)
