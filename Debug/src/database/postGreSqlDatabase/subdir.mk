################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/database/postGreSqlDatabase/aletheiaDatabase.cpp 

OBJS += \
./src/database/postGreSqlDatabase/aletheiaDatabase.o 

CPP_DEPS += \
./src/database/postGreSqlDatabase/aletheiaDatabase.d 


# Each subdirectory must supply rules for building sources it contributes
src/database/postGreSqlDatabase/%.o: ../src/database/postGreSqlDatabase/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I"/home/vermosen/eclipse/aletheia/src" -I/usr/include/postgresql/ -I/usr/local/include/soci/ -O0 -g3 -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


