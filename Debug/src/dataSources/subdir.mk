################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataSources/quandl.cpp 

OBJS += \
./src/dataSources/quandl.o 

CPP_DEPS += \
./src/dataSources/quandl.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataSources/%.o: ../src/dataSources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/eclipse/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


