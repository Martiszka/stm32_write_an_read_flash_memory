################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Flash_write_and_read.c 

OBJS += \
./HAL_Driver/Flash_write_and_read.o 

C_DEPS += \
./HAL_Driver/Flash_write_and_read.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/%.o: ../HAL_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RBTx -DNUCLEO_F103RB -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -I"C:/Users/Marta/workspace/STM32F1_flash_memory/HAL_Driver/Inc/Legacy" -I"C:/Users/Marta/workspace/STM32F1_flash_memory/Utilities/STM32F1xx_Nucleo" -I"C:/Users/Marta/workspace/STM32F1_flash_memory/inc" -I"C:/Users/Marta/workspace/STM32F1_flash_memory/CMSIS/device" -I"C:/Users/Marta/workspace/STM32F1_flash_memory/CMSIS/core" -I"C:/Users/Marta/workspace/STM32F1_flash_memory/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


