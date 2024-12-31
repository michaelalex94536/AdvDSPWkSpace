################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/clock.c \
../Src/fifo.c \
../Src/lowpassfilter.c \
../Src/main.c \
../Src/signals.c \
../Src/sine_generator.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/clock.o \
./Src/fifo.o \
./Src/lowpassfilter.o \
./Src/main.o \
./Src/signals.o \
./Src/sine_generator.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/clock.d \
./Src/fifo.d \
./Src/lowpassfilter.d \
./Src/main.d \
./Src/signals.d \
./Src/sine_generator.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -D__FPU_PRESENT -DSTM32F411xE -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DARM_MATH_CM4 -c -I../Inc -I"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/10_RealtimeDSP_SensorDataBlocksV2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/10_RealtimeDSP_SensorDataBlocksV2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/10_RealtimeDSP_SensorDataBlocksV2/chip_headers/CMSIS/DSP/Include" -I"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/10_RealtimeDSP_SensorDataBlocksV2/chip_headers/CMSIS/Include" -I"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/10_RealtimeDSP_SensorDataBlocksV2/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/clock.cyclo ./Src/clock.d ./Src/clock.o ./Src/clock.su ./Src/fifo.cyclo ./Src/fifo.d ./Src/fifo.o ./Src/fifo.su ./Src/lowpassfilter.cyclo ./Src/lowpassfilter.d ./Src/lowpassfilter.o ./Src/lowpassfilter.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/signals.cyclo ./Src/signals.d ./Src/signals.o ./Src/signals.su ./Src/sine_generator.cyclo ./Src/sine_generator.d ./Src/sine_generator.o ./Src/sine_generator.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/tim.cyclo ./Src/tim.d ./Src/tim.o ./Src/tim.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src
