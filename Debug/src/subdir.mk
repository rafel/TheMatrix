################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Environment.cpp \
../src/GameCore.cpp \
../src/Hall.cpp \
../src/Image.cpp \
../src/Shader.cpp \
../src/Window.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/Environment.o \
./src/GameCore.o \
./src/Hall.o \
./src/Image.o \
./src/Shader.o \
./src/Window.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/Environment.d \
./src/GameCore.d \
./src/Hall.d \
./src/Image.d \
./src/Shader.d \
./src/Window.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/x86_64-linux-gnu -I/home/rafel/Downloads/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


