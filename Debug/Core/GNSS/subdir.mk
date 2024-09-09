################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/GNSS/GNSS.c 

OBJS += \
./Core/GNSS/GNSS.o 

C_DEPS += \
./Core/GNSS/GNSS.d 


# Each subdirectory must supply rules for building sources it contributes
Core/GNSS/%.o Core/GNSS/%.su Core/GNSS/%.cyclo: ../Core/GNSS/%.c Core/GNSS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I"C:/STWorkspace/GNSS_Driver/Core/GNSS" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/STWorkspace/GNSS_Driver/Core/SysTick_Timer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-GNSS

clean-Core-2f-GNSS:
	-$(RM) ./Core/GNSS/GNSS.cyclo ./Core/GNSS/GNSS.d ./Core/GNSS/GNSS.o ./Core/GNSS/GNSS.su

.PHONY: clean-Core-2f-GNSS

