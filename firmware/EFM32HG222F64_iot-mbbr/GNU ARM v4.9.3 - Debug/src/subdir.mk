################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BG96_at_driver.c \
../src/DS18B20.c \
../src/VL43L1X.c \
../src/adc.c \
../src/delay.c \
../src/i2c.c \
../src/interrupt.c \
../src/main.c \
../src/serlcd.c \
../src/util.c \
../src/util_string.c 

OBJS += \
./src/BG96_at_driver.o \
./src/DS18B20.o \
./src/VL43L1X.o \
./src/adc.o \
./src/delay.o \
./src/i2c.o \
./src/interrupt.o \
./src/main.o \
./src/serlcd.o \
./src/util.o \
./src/util_string.o 

C_DEPS += \
./src/BG96_at_driver.d \
./src/DS18B20.d \
./src/VL43L1X.d \
./src/adc.d \
./src/delay.d \
./src/i2c.d \
./src/interrupt.d \
./src/main.d \
./src/serlcd.d \
./src/util.d \
./src/util_string.d 


# Each subdirectory must supply rules for building sources it contributes
src/BG96_at_driver.o: ../src/BG96_at_driver.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/BG96_at_driver.d" -MT"src/BG96_at_driver.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/DS18B20.o: ../src/DS18B20.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/DS18B20.d" -MT"src/DS18B20.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/VL43L1X.o: ../src/VL43L1X.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/VL43L1X.d" -MT"src/VL43L1X.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/adc.o: ../src/adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/adc.d" -MT"src/adc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/delay.o: ../src/delay.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/delay.d" -MT"src/delay.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/i2c.o: ../src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/i2c.d" -MT"src/i2c.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/interrupt.o: ../src/interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/interrupt.d" -MT"src/interrupt.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/serlcd.o: ../src/serlcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/serlcd.d" -MT"src/serlcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/util.o: ../src/util.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/util.d" -MT"src/util.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/util_string.o: ../src/util_string.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/util_string.d" -MT"src/util_string.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


