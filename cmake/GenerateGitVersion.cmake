execute_process(
            COMMAND git describe --tags --always HEAD
            OUTPUT_VARIABLE GITVERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE)
            #string(REGEX MATCH "[0-9]+" VERSION ${VERSION})
            CONFIGURE_FILE(${SRC} ${DEST} @ONLY)
