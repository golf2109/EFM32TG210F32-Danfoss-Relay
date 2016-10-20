################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32tg/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: EFM32TG210F32.axf

# Tool invocations
EFM32TG210F32.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "EFM32TG210F32.ld" -Xlinker --gc-sections -Xlinker -Map="EFM32TG210F32.map" --specs=nano.specs -o EFM32TG210F32.axf "./src/InitDevice.o" "./src/main.o" "./emlib/em_cmu.o" "./emlib/em_dma.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_leuart.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./CMSIS/efm32tg/startup_gcc_efm32tg.o" "./CMSIS/efm32tg/system_efm32tg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: EFM32TG210F32.hex'
	arm-none-eabi-objcopy -O ihex "EFM32TG210F32.axf" "EFM32TG210F32.hex"
	@echo ' '

	@echo 'Building bin file: EFM32TG210F32.bin'
	arm-none-eabi-objcopy -O binary "EFM32TG210F32.axf" "EFM32TG210F32.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "EFM32TG210F32.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) EFM32TG210F32.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
