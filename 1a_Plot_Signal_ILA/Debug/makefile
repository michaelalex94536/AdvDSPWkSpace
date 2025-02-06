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


BUILD_ARTIFACT_NAME := 1a_Plot_Signal_ILA
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
1a_Plot_Signal_ILA.elf \

MAP_FILES += \
1a_Plot_Signal_ILA.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
1a_Plot_Signal_ILA.list \


# All Target
all: main-build

# Main-build Target
main-build: 1a_Plot_Signal_ILA.elf secondary-outputs

# Tool invocations
<<<<<<< HEAD
1a_Plot_Signal_ILA.elf 1a_Plot_Signal_ILA.map: $(OBJS) $(USER_OBJS) /home/michael/Documents/STM32Code/AdvDSPWkSpace/1a_Plot_Signal_ILA/STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "1a_Plot_Signal_ILA.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/michael/Documents/STM32Code/AdvDSPWkSpace/1a_Plot_Signal_ILA/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="1a_Plot_Signal_ILA.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
=======
1a_Plot_Signal_ILA.elf 1a_Plot_Signal_ILA.map: $(OBJS) $(USER_OBJS) /home/michael/Documents/STCode/AdvDSPWkSpace/1a_Plot_Signal_ILA/STM32F411RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "1a_Plot_Signal_ILA.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/michael/Documents/STCode/AdvDSPWkSpace/1a_Plot_Signal_ILA/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="1a_Plot_Signal_ILA.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
>>>>>>> 9f55a9437343cddf789b5bf99c5d0c9cf60499bb
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

1a_Plot_Signal_ILA.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "1a_Plot_Signal_ILA.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 1a_Plot_Signal_ILA.elf 1a_Plot_Signal_ILA.list 1a_Plot_Signal_ILA.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
