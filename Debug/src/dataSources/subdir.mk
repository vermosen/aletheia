################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataSources/pepperstone.cpp \
../src/dataSources/quandl.cpp \
../src/dataSources/yahoo.cpp 

OBJS += \
./src/dataSources/pepperstone.o \
./src/dataSources/quandl.o \
./src/dataSources/yahoo.o 

CPP_DEPS += \
./src/dataSources/pepperstone.d \
./src/dataSources/quandl.d \
./src/dataSources/yahoo.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataSources/%.o: ../src/dataSources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/eclipse/aletheia/src" -I/usr/include/postgresql/ -I/usr/local/include/soci/ -O0 -g3 -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


