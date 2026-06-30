cmake_minimum_required(VERSION 3.20)

project(LastMinuteLifeSaver)

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
)

target_include_directories(app PRIVATE
    include
    models
    routes
    src
)

if(WIN32)
    target_link_libraries(app ws2_32)
endif()