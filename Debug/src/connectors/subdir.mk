################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/connectors/http.cpp \
../src/connectors/ssl.cpp 

OBJS += \
./src/connectors/http.o \
./src/connectors/ssl.o 

CPP_DEPS += \
./src/connectors/http.d \
./src/connectors/ssl.d 


# Each subdirectory must supply rules for building sources it contributes
src/connectors/%.o: ../src/connectors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/eclipse/aletheia/src" -I/usr/include/postgresql/ -I/usr/local/include/soci/ -O0 -g3 -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


