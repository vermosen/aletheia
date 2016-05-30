################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataSource/quandl.cpp 

OBJS += \
./src/dataSource/quandl.o 

CPP_DEPS += \
./src/dataSource/quandl.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataSource/%.o: ../src/dataSource/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/vermosen/git/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


