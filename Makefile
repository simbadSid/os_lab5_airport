CC     	= gcc
CFLAGS 	= -Wall -Werror -g -pthread
SRC_DIR	= src/
BIN_DIR	= bin/s
EXEC   	=	planeManager_question1	\
		planeManager_question2	\
		planeManager_question3	\
		planeManager_question4
all   	: $(EXEC)










#-----------------------------------------------------------------------------------------------------------
#----------------------------------------------- Executables -----------------------------------------------
#-----------------------------------------------------------------------------------------------------------
planeManager_question1	: $(BIN_DIR)planeManager_question1.o $(BIN_DIR)shared.o
			$(CC) $(CFLAGS) -o $@ $^


planeManager_question2	: $(BIN_DIR)planeManager_question2.o $(BIN_DIR)shared.o
			$(CC) $(CFLAGS) -o $@ $^


planeManager_question3	: $(BIN_DIR)planeManager_question3.o $(BIN_DIR)shared.o
			$(CC) $(CFLAGS) -o $@ $^


planeManager_question4	: $(BIN_DIR)planeManager_question4.o $(BIN_DIR)shared.o
			$(CC) $(CFLAGS) -o $@ $^


#-----------------------------------------------------------------------------------------------------------
#----------------------------------------------- Binaries --------------------------------------------------
#-----------------------------------------------------------------------------------------------------------
$(BIN_DIR)%_question1.o	: $(SRC_DIR)question1/%.c
			$(CC) $(CFLAGS) -c -o $@ $^


$(BIN_DIR)%_question2.o	: $(SRC_DIR)question2/%.c
			$(CC) $(CFLAGS) -c -o $@ $^


$(BIN_DIR)%_question3.o	: $(SRC_DIR)question3/%.c
			$(CC) $(CFLAGS) -c -o $@ $^


$(BIN_DIR)%_question4.o	: $(SRC_DIR)question4/%.c
			$(CC) $(CFLAGS) -c -o $@ $^


$(BIN_DIR)%.o		: $(SRC_DIR)sharedFile/%.c
			$(CC) $(CFLAGS) -c -o $@ $^


#-----------------------------------------------------------------------------------------------------------
#---------------------------------------- General Methodes -------------------------------------------------
#-----------------------------------------------------------------------------------------------------------
.PHONY	: clean mrproper


clean:
	rm -f $(BIN_DIR)*.o


mrproper: clean
	rm -rf $(EXEC)
