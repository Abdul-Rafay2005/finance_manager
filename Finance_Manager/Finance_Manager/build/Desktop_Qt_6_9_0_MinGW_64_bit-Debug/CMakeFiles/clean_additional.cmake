# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FinanceManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FinanceManager_autogen.dir\\ParseCache.txt"
  "FinanceManager_autogen"
  )
endif()
