C_SRCS += \
./sources/calcul_arith.c \
./sources/convertisseur.c \
./sources/elem.c \
./sources/linear_struct.c \
./sources/main.c \
./sources/messages.c \
./sources/tools.c 

C_DEPS += \
./binaries/calcul_arith.d \
./binaries/convertisseur.d \
./binaries/elem.d \
./binaries/linear_struct.d \
./binaries/main.d \
./binaries/messages.d \
./binaries/tools.d 

OBJS += \
./binaries/calcul_arith.o \
./binaries/convertisseur.o \
./binaries/elem.o \
./binaries/linear_struct.o \
./binaries/main.o \
./binaries/messages.o \
./binaries/tools.o 

binaries/%.o: ./sources/%.c
	@echo 'Construction du fichier: $<'
	@echo 'Invocation: GCC C Compiler'
	gcc -I"./headers" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Construction terminee: $<'
	@echo ' '


