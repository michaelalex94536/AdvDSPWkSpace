################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


<<<<<<< HEAD
BUILD_ARTIFACT_NAME := 6_RealtimeDSP
=======
BUILD_ARTIFACT_NAME := 9a_Filtering
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
<<<<<<< HEAD
6_RealtimeDSP.elf \

MAP_FILES += \
6_RealtimeDSP.map \
=======
9a_Filtering.elf \

MAP_FILES += \
9a_Filtering.map \
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
<<<<<<< HEAD
6_RealtimeDSP.list \
=======
9a_Filtering.list \
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918


# All Target
all: main-build

# Main-build Target
<<<<<<< HEAD
main-build: 6_RealtimeDSP.elf secondary-outputs

# Tool invocations
6_RealtimeDSP.elf 6_RealtimeDSP.map: $(OBJS) $(USER_OBJS) /Users/michaelalex/Documents/Git/AdvDSPWkSpace/6_RealtimeDSP/STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "6_RealtimeDSP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/6_RealtimeDSP/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="6_RealtimeDSP.map" -Wl,--gc-sections -static -L"/Users/michaelalex/Documents/Git/AdvDSPWkSpace/6_RealtimeDSP/chip_headers/CMSIS/Lib/GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
=======
main-build: 9a_Filtering.elf secondary-outputs

# Tool invocations
9a_Filtering.elf 9a_Filtering.map: $(OBJS) $(USER_OBJS) /home/michael/Documents/STCode/AdvDSPWkSpace/9a_Filtering/STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "9a_Filtering.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/michael/Documents/STCode/AdvDSPWkSpace/9a_Filtering/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="9a_Filtering.map" -Wl,--gc-sections -static -L"/home/michael/Documents/STCode/AdvDSPWkSpace/9a_Filtering/chip_headers/CMSIS/Lib/GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

<<<<<<< HEAD
6_RealtimeDSP.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "6_RealtimeDSP.list"
=======
9a_Filtering.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "9a_Filtering.list"
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
<<<<<<< HEAD
	-$(RM) 6_RealtimeDSP.elf 6_RealtimeDSP.list 6_RealtimeDSP.map default.size.stdout
=======
	-$(RM) 9a_Filtering.elf 9a_Filtering.list 9a_Filtering.map default.size.stdout
>>>>>>> ec4d98f13383575572cc0c5d68b71b335edff918
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
