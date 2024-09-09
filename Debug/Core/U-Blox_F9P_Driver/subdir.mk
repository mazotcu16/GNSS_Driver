################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.c 

OBJS += \
./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.o 

C_DEPS += \
./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/U-Blox_F9P_Driver/%.o Core/U-Blox_F9P_Driver/%.su Core/U-Blox_F9P_Driver/%.cyclo: ../Core/U-Blox_F9P_Driver/%.c Core/U-Blox_F9P_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I"C:/STWorkspace/GNSS_Driver/Core/U-Blox_F9P_Driver" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-U-2d-Blox_F9P_Driver

clean-Core-2f-U-2d-Blox_F9P_Driver:
	-$(RM) ./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.cyclo ./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.d ./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.o ./Core/U-Blox_F9P_Driver/U-Blox_F9P_Driver.su

.PHONY: clean-Core-2f-U-2d-Blox_F9P_Driver

