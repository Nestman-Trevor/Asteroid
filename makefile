###############################################################
# Program:
#     Project 04, Asteroids
#     Brother Comeau, CS165
# Author:
#     Trevor Nestman
# Summary:
#     Enter a brief description of your program here! If you do any
#     extra credit, this would be a good place to describe it.
#       The extra content should be pretty noticable.
#           - Score
#           - Two Players
#           - Custom asteroid that I built
#           - Winner is the first to over 9,000
#           - Guns fire automatically
#           - Nice color
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################

# for the linux VM in vmware, you need to add '-lGL' to LFLAGS
LFLAGS = -lGL -lglut -lGLU

# vars for the backup feature
PACKAGE   = backup
VERSION   = ` date +"%Y%m%d_%H%M%S" `
ARCHIVE   = $(PACKAGE)-$(VERSION)

###############################################################
# Programs:
#    moon:         The moon lander game
###############################################################
a.out: game.o uiInteract.o uiDraw.o point.o velocity.o movable.o ship.o bullet.o asteroid.o
	g++ -o a.out game.o uiInteract.o uiDraw.o point.o velocity.o movable.o ship.o bullet.o asteroid.o$(LFLAGS)
	tar -j -cf project4.tar makefile *.h *.cpp

###############################################################
# Individual files
#    rifle.o       Displays the rifle
#    game.o        The skeet game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
#    velocity.o    velocity class
###############################################################
game.o: game.cpp uiDraw.h uiInteract.h point.h
	g++ -c game.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

movable.o: movable.cpp movable.h velocity.h uidraw.h
    g++ -c movable.cpp

ship.o: ship.cpp ship.h movable.h
    g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h movable.h velocity.h
    g++ -c bullet.cpp

asteroid.o: asteroid.cpp asteroid.h movable.h
    g++ -c asteroid.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out project4.tar *.o

cleanbackups:
	rm backup*.tar

backup:
	tar -j -cvf $(ARCHIVE).tar *.cpp *.h makefile

all:
	a.out
