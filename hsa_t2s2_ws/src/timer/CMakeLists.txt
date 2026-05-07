cmake_minimum_required(VERSION 3.16.3)

project(timer C ASM)


find_package(atmega32_uart REQUIRED QUIET)
find_package(atmega32_adc REQUIRED QUIET)


###############################################################################
#          Apps
###############################################################################


set(APP_TARGETS
    timer_blink
    timer_pwm
    timer_pwm_adc
    timer_servo
    timer_sensor
    timer_servo_sensor
)
list(APPEND PROJECT_APP_TARGETS ${APP_TARGETS})


foreach(target ${APP_TARGETS})
    message(STATUS "target = " ${target})

    add_executable(${target} ${HEADERS}
        src/applications/main_${target}.c
    )

    target_link_libraries(${target}
        atmega32_uart
        atmega32_adc
    )

endforeach()



# additional targets for all app targets
foreach(target ${PROJECT_APP_TARGETS})
    avr_target_disasm(${target})

    avr_target_create_map(${target})
    avr_target_create_hex(${target})

    avr_target_add_prog_target(${target})
endforeach()



###############################################################################
#           Export
###############################################################################

set(DEVEL_DIR ${PROJECT_SOURCE_DIR}/devel)

foreach(target ${PROJECT_APP_TARGETS})
    add_custom_target(devel_${target} ALL
        DEPENDS ${target}
        COMMAND mkdir -p ${DEVEL_DIR}
        COMMAND cp ${PROJECT_BINARY_DIR}/${target}.hex ${DEVEL_DIR}/
        COMMAND cp ${PROJECT_BINARY_DIR}/${target}.map ${DEVEL_DIR}/
        COMMAND cp ${PROJECT_BINARY_DIR}/${target}.lss ${DEVEL_DIR}/
        COMMAND cp ${PROJECT_BINARY_DIR}/${target} ${DEVEL_DIR}/${target}.elf
        # COMMAND cp ${PROJECT_BINARY_DIR}/${target} ${PROJECT_SOURCE_DIR}/${target}.elf
    )
endforeach()


# Create project target for global management
btk_project(
    TARGETS ${LIB_TARGETS} ${PROJECT_APP_TARGETS}
)




