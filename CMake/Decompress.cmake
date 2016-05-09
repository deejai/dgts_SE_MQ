# The purpose of this file is to provide a CMake function that allows for
# a compressed file to be decompressed.
#
# This module requires ${THIRD_PARTY_DIR} to point to the third party folder
# that contains the compressed ThirdParty files.
#
# If the user is in Windows, 7Zip will be used to decompress files. Therefore,
# $(THIRD_PARTY_DIR}/7zip/7za.exe must exist.
#
# If the user is in Linux then the tar command is used so we don't need any
# extraction program like 7Zip.

if(WIN32)
    find_program(7ZIP_EXE NAME 7za.exe PATHS "${THIRD_PARTY_DIR}/7zip")
    if(NOT 7ZIP_EXE)
        message("7zip was not found!")
    endif()
endif()

function(decompress archive_path)
  set (extra_macro_args ${ARGN})
  list(LENGTH extra_macro_args num_extra_args)
  if (${num_extra_args} GREATER 0)
    list(GET extra_macro_args 0 extract_path)
  else()
    set(extract_path ${THIRD_PARTY_DIR})
  endif()

  message("Extracting ${archive_path} to ${extract_path}...")
  if(7ZIP_EXE)
      set(7Z_ARGS x -o${extract_path}/ ${archive_path})
      execute_process(COMMAND ${7ZIP_EXE} ${7Z_ARGS} OUTPUT_VARIABLE 7Z_OUTPUT)
  else()
      set(TAR_COMMANDS tar xf ${archive_path} --directory=${extract_path})
      execute_process(COMMAND ${TAR_COMMANDS} OUTPUT_VARIABLE TAR_OUT)
  endif()
endfunction(decompress)
