RM := rm -rf
# 32 ou 64 bits
ARCHI := 32

# Toutes les sources necessaires
-include compil/directives.mk
-include compil/comp_$(ARCHI)bits.mk

all: projetlong

projetlong: $(OBJS) $(USER_OBJS)
	@echo 'Construction de la cible: $@'
	@echo 'Invocation: GCC C Linker'
	gcc -ansi -pedantic -o"projetlong" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Cible construite: $@'
	@echo ' '

clean:
	-$(RM) $(C_DEPS)$(OBJS)$(EXECUTABLES) projetlong
	-@echo ' '
