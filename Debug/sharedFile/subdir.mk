################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sharedFile/shared.c 

OBJS += \
./sharedFile/shared.o 

C_DEPS += \
./sharedFile/shared.d 


# Each subdirectory must supply rules for building sources it contributes
sharedFile/%.o: ../sharedFile/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


