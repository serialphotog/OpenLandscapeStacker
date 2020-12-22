set(OLS_SRCS
  main.cpp
  core/frame.cpp
  ui/main_window.cpp
  ${TS_FILES}
)
include_directories(.)

add_executable(${PROJECT_NAME} ${OLS_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets ${OpenCV_LIBS})
qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
