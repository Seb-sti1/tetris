#add_executable(tetris main.cpp graphicmatrix.h graphicmatrix.cpp MainWindow.h MainWindow.cpp matrix.h)
add_executable(tetris matrix_test.cpp matrix.h)

#link_libraries(tetris ${GTKMM_LIBRARIES})