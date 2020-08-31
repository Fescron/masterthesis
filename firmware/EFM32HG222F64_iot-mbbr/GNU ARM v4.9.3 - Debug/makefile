################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include emdrv/subdir.mk
-include dbprint/subdir.mk
-include VL53L1X_PLATFORM/subdir.mk
-include VL53L1X_API/subdir.mk
-include CMSIS/EFM32HG/subdir.mk
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
all: EFM32HG222F64_iot-mbbr.axf

# Tool invocations
EFM32HG222F64_iot-mbbr.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "EFM32HG222F64_iot-mbbr.ld" -Xlinker --gc-sections -Xlinker -Map="EFM32HG222F64_iot-mbbr.map" --specs=nano.specs -o EFM32HG222F64_iot-mbbr.axf "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./CMSIS/EFM32HG/startup_efm32hg.o" "./CMSIS/EFM32HG/system_efm32hg.o" "./src/BG96_at_driver.o" "./src/DS18B20.o" "./src/adc.o" "./src/delay.o" "./src/i2c.o" "./src/interrupt.o" "./src/main.o" "./src/serlcd.o" "./src/util.o" "./src/util_string.o" "./dbprint/dbprint.o" "./VL53L1X_PLATFORM/vl53l1_platform.o" "./VL53L1X_API/VL53L1X_api.o" "./VL53L1X_API/VL53L1X_calibration.o" "./emdrv/ustimer.o" "./emlib/em_adc.o" "./emlib/em_i2c.o" "./emlib/em_rtc.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./src/VL43L1X.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: EFM32HG222F64_iot-mbbr.hex'
	arm-none-eabi-objcopy -O ihex "EFM32HG222F64_iot-mbbr.axf" "EFM32HG222F64_iot-mbbr.hex"
	@echo ' '

	@echo 'Building bin file: EFM32HG222F64_iot-mbbr.bin'
	arm-none-eabi-objcopy -O binary "EFM32HG222F64_iot-mbbr.axf" "EFM32HG222F64_iot-mbbr.bin"
	@echo ' '

	@echo 'Building s37 file: EFM32HG222F64_iot-mbbr.s37'
	arm-none-eabi-objcopy -O srec "EFM32HG222F64_iot-mbbr.axf" "EFM32HG222F64_iot-mbbr.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "EFM32HG222F64_iot-mbbr.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) EFM32HG222F64_iot-mbbr.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
