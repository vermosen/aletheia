################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataFile/jsonFile.cpp 

OBJS += \
./src/dataFile/jsonFile.o 

CPP_DEPS += \
./src/dataFile/jsonFile.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataFile/%.o: ../src/dataFile/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/vermosen/git/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


