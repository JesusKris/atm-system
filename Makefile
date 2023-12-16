objects = src/main.o src/users/user.o src/authentication/auth.o src/accounts/account.o src/drawing/draw.o src/utilities/utility.o

atm : $(objects)
	cc -o atm $(objects)

main.o : src/header.h
kbd.o : src/header.h
command.o : src/header.h
display.o : src/header.h
insert.o : src/header.h
search.o : src/header.h
files.o : src/header.h
utils.o : src/header.h

clean :
	rm -f $(objects)
