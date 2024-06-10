################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Source/keypad.c \
../HAL/Source/lcd.c 

OBJS += \
./HAL/Source/keypad.o \
./HAL/Source/lcd.o 

C_DEPS += \
./HAL/Source/keypad.d \
./HAL/Source/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Source/%.o: ../HAL/Source/%.c HAL/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


