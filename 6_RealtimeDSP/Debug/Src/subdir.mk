################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/lowpassfilter.c \
../Src/main.c \
../Src/signals.c \
../Src/sine_generator.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/uart.c 

OBJS += \
./Src/lowpassfilter.o \
./Src/main.o \
./Src/signals.o \
./Src/sine_generator.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/uart.o 

C_DEPS += \
./Src/lowpassfilter.d \
./Src/main.d \
./Src/signals.d \
./Src/sine_generator.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -D__FPU_PRESENT -DSTM32F411xE -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DARM_MATH_CM4 -c -I../Inc -I"/home/michael/Documents/Udemy/AdvDSPonARM/AdvDSPWkSpace/6_RealtimeDSP/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/michael/Documents/Udemy/AdvDSPonARM/AdvDSPWkSpace/6_RealtimeDSP/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/michael/Documents/Udemy/AdvDSPonARM/AdvDSPWkSpace/6_RealtimeDSP/chip_headers/CMSIS/DSP/Include" -I"/home/michael/Documents/Udemy/AdvDSPonARM/AdvDSPWkSpace/6_RealtimeDSP/chip_headers/CMSIS/Include" -I"/home/michael/Documents/Udemy/AdvDSPonARM/AdvDSPWkSpace/6_RealtimeDSP/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/lowpassfilter.cyclo ./Src/lowpassfilter.d ./Src/lowpassfilter.o ./Src/lowpassfilter.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/signals.cyclo ./Src/signals.d ./Src/signals.o ./Src/signals.su ./Src/sine_generator.cyclo ./Src/sine_generator.d ./Src/sine_generator.o ./Src/sine_generator.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

