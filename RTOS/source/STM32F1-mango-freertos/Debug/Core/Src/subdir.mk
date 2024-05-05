################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/user-common.c \
../Core/Src/user-gpio.c \
../Core/Src/user-it.c \
../Core/Src/user-task01.c \
../Core/Src/user-task02.c \
../Core/Src/user-task03.c \
../Core/Src/user-task04.c \
../Core/Src/user-task05.c \
../Core/Src/user-task06.c \
../Core/Src/user-task07.c \
../Core/Src/user-task08.c \
../Core/Src/user-uart.c 

OBJS += \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/user-common.o \
./Core/Src/user-gpio.o \
./Core/Src/user-it.o \
./Core/Src/user-task01.o \
./Core/Src/user-task02.o \
./Core/Src/user-task03.o \
./Core/Src/user-task04.o \
./Core/Src/user-task05.o \
./Core/Src/user-task06.o \
./Core/Src/user-task07.o \
./Core/Src/user-task08.o \
./Core/Src/user-uart.o 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/user-common.d \
./Core/Src/user-gpio.d \
./Core/Src/user-it.d \
./Core/Src/user-task01.d \
./Core/Src/user-task02.d \
./Core/Src/user-task03.d \
./Core/Src/user-task04.d \
./Core/Src/user-task05.d \
./Core/Src/user-task06.d \
./Core/Src/user-task07.d \
./Core/Src/user-task08.d \
./Core/Src/user-uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/user-common.cyclo ./Core/Src/user-common.d ./Core/Src/user-common.o ./Core/Src/user-common.su ./Core/Src/user-gpio.cyclo ./Core/Src/user-gpio.d ./Core/Src/user-gpio.o ./Core/Src/user-gpio.su ./Core/Src/user-it.cyclo ./Core/Src/user-it.d ./Core/Src/user-it.o ./Core/Src/user-it.su ./Core/Src/user-task01.cyclo ./Core/Src/user-task01.d ./Core/Src/user-task01.o ./Core/Src/user-task01.su ./Core/Src/user-task02.cyclo ./Core/Src/user-task02.d ./Core/Src/user-task02.o ./Core/Src/user-task02.su ./Core/Src/user-task03.cyclo ./Core/Src/user-task03.d ./Core/Src/user-task03.o ./Core/Src/user-task03.su ./Core/Src/user-task04.cyclo ./Core/Src/user-task04.d ./Core/Src/user-task04.o ./Core/Src/user-task04.su ./Core/Src/user-task05.cyclo ./Core/Src/user-task05.d ./Core/Src/user-task05.o ./Core/Src/user-task05.su ./Core/Src/user-task06.cyclo ./Core/Src/user-task06.d ./Core/Src/user-task06.o ./Core/Src/user-task06.su ./Core/Src/user-task07.cyclo ./Core/Src/user-task07.d ./Core/Src/user-task07.o ./Core/Src/user-task07.su ./Core/Src/user-task08.cyclo ./Core/Src/user-task08.d ./Core/Src/user-task08.o ./Core/Src/user-task08.su ./Core/Src/user-uart.cyclo ./Core/Src/user-uart.d ./Core/Src/user-uart.o ./Core/Src/user-uart.su

.PHONY: clean-Core-2f-Src

