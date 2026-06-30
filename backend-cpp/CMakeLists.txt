cmake_minimum_required(VERSION 3.20)

project(LastMinuteLifeSaver)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(app
    main.cpp
    models/Task.cpp
    src/TaskManager.cpp
    routes/TaskRoutes.cpp
    routes/AnalyticsRoutes.cpp
    routes/UpdateTaskRoutes.cpp
    routes/PriorityRoutes.cpp
    services/PriorityEngine.cpp
    utils/DateUtils.cpp
    services/RiskAnalyzer.cpp
    services/RecommendationEngine.cpp
    routes/PlannerRoutes.cpp
    services/GeminiService.cpp
)

target_include_directories(app PRIVATE
    include
    models
    routes
    src
)

target_compile_definitions(app PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
if(WIN32)
    target_link_libraries(app ws2_32 crypt32 OpenSSL::SSL OpenSSL::Crypto)
else()
    target_link_libraries(app OpenSSL::SSL OpenSSL::Crypto)
endif()