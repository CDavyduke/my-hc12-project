file project.o
set remotebaud 38400
target dbug12 ttylink
load
set *0xb34 = 0
set *0xb36 = 0
set *0xdb4e = 0x84ff