################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataFile.cpp \
../src/database.cpp \
../src/main.cpp 

OBJS += \
./src/dataFile.o \
./src/database.o \
./src/main.o 

CPP_DEPS += \
./src/dataFile.d \
./src/database.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/eclipse/aletheia/src" -I/usr/include/postgresql/ -I/usr/local/include/soci/ -O0 -g3 -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


