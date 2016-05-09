# If we run our executables directly they'll crash because they wont be able to 
# find the third party binaries that they're linked against because those third
# parties were left in their original directory instead of being copied to the
# build directory.
#
# If however, the third party binary paths were added to the system PATH then
# the executables would run fine. Therefore, we'll create batch files that
# do just that...
if(WIN32)

    #Write the release and debug bat files to run SE_MQ
    set(SE_MQ_THIRD_PARTIES "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE};${BOOST_RELEASE_BIN_DIR};${RABITMQC_BIN_DIR};${SIMPLEAMQPCLIENT_BIN_DIR}")
    file(WRITE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/SE_MQ.bat" "set PATH=${SE_MQ_THIRD_PARTIES};%PATH%\n")
    file(APPEND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/SE_MQ.bat" "SE_MQ.exe")

    # Debug
    set(SE_MQ_DEBUG_THIRD_PARTIES "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG};${BOOST_DEBUG_BIN_DIR};${RABITMQC_BIN_DIR};${SIMPLEAMQPCLIENT_BIN_DIR}")
    file(WRITE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/SE_MQ.bat" "set PATH=${SE_MQ_DEBUG_THIRD_PARTIES};%PATH%\n")
    file(APPEND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/SE_MQ.bat" "SE_MQ.exe")    

else(WIN32)
# LINUX TODO

endif(WIN32)
