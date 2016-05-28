################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/connector/quandl.cpp \
../src/connector/ssl.cpp 

OBJS += \
./src/connector/quandl.o \
./src/connector/ssl.o 

CPP_DEPS += \
./src/connector/quandl.d \
./src/connector/ssl.d 


# Each subdirectory must supply rules for building sources it contributes
src/connector/%.o: ../src/connector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/vermosen/git/aletheia/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


