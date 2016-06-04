################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataFiles/csv.cpp \
../src/dataFiles/json.cpp \
../src/dataFiles/xml.cpp 

OBJS += \
./src/dataFiles/csv.o \
./src/dataFiles/json.o \
./src/dataFiles/xml.o 

CPP_DEPS += \
./src/dataFiles/csv.d \
./src/dataFiles/json.d \
./src/dataFiles/xml.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataFiles/%.o: ../src/dataFiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/git/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


