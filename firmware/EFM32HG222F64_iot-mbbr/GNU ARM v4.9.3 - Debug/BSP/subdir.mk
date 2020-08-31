################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/hardware/kit/common/bsp/bsp_stk_leds.c 

OBJS += \
./BSP/bsp_stk_leds.o 

C_DEPS += \
./BSP/bsp_stk_leds.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/bsp_stk_leds.o: /home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4/hardware/kit/common/bsp/bsp_stk_leds.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFM32HG222F64=1' -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/dbprint" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_API" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/VL53L1X_PLATFORM" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/common/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/config" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emdrv/ustimer/inc" -I"/home/brecht/SimplicityStudio/v4_workspace/EFM32HG222F64_iot-mbbr/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/CMSIS/Include" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/emlib/inc" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//hardware/kit/common/bsp" -I"/home/brecht/Programs/SimplicityStudio_v4/developer/sdks/gecko_sdk_suite/v2.4//platform/Device/SiliconLabs/EFM32HG/Include" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"BSP/bsp_stk_leds.d" -MT"BSP/bsp_stk_leds.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


