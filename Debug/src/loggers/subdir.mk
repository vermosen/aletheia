################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/loggers/consoleLogger.cpp 

OBJS += \
./src/loggers/consoleLogger.o 

CPP_DEPS += \
./src/loggers/consoleLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/loggers/%.o: ../src/loggers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/vermosen/git/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


