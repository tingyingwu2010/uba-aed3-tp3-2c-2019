if(EXISTS "/home/franco/Escritorio/uba-aed3-tp3-2c-2019/cvrp_test[1]_tests.cmake")
  include("/home/franco/Escritorio/uba-aed3-tp3-2c-2019/cvrp_test[1]_tests.cmake")
else()
  add_test(cvrp_test_NOT_BUILT cvrp_test_NOT_BUILT)
endif()