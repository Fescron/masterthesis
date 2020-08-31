################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_adc.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_assert.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_cmu.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_core.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_emu.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_gpio.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_i2c.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_rtc.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_timer.c \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_usart.c 

OBJS += \
./emlib/em_adc.o \
./emlib/em_assert.o \
./emlib/em_cmu.o \
./emlib/em_core.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_i2c.o \
./emlib/em_rtc.o \
./emlib/em_timer.o \
./emlib/em_usart.o 

C_DEPS += \
./emlib/em_adc.d \
./emlib/em_assert.d \
./emlib/em_cmu.d \
./emlib/em_core.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_i2c.d \
./emlib/em_rtc.d \
./emlib/em_timer.d \
./emlib/em_usart.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_adc.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_adc.d" -MT"emlib/em_adc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_assert.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_assert.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_assert.d" -MT"emlib/em_assert.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_core.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_core.d" -MT"emlib/em_core.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_i2c.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_i2c.d" -MT"emlib/em_i2c.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_rtc.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_rtc.d" -MT"emlib/em_rtc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_timer.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_timer.d" -MT"emlib/em_timer.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_usart.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/platform/emlib/src/em_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"emlib/em_usart.d" -MT"emlib/em_usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


