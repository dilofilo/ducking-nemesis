#Directories
OUTPUT=output/
OBJECT=obj/
SOURCE=src/

#Compiler Variables
COMPILE=g++ 
CFLAGS=-w -std=c++11
LIBRARIES= -lGL -lGLU -lglut -lglui -lSDL

#Object file dependencies
ball.h: includes.h table.h
ballThreads.h: includes.h
menu.h: includes.h screenSaver.h
skybox.h: includes.h
table.h: includes.h

#preprocessor macros passed using -D<macro> option
Debug: -DDEBUG
ballDebug: -DBALL_DEBUG
tableDebug: -DTABLE_DEBUG
threadDebug: -DTHREAD_DEBUG
solveDebug: -DSOLVE_DEBUG
handlerDebug: -DHANDLER_DEBUG
initDebug: -DINIT_DEBUG
skyboxDebug: -DSKYBOX_DEBUG	
menuDebug: -DMENU_DEBUG
#Document Generation


#make file modes
debugger: $(OUTPUT)runDebugger
	cd $(OUTPUT); ./finalDebugger $(num_threads) 
	  
debug: $(OUTPUT)runDebug
	cd $(OUTPUT); ./finalDebug $(num_threads) >log.txt

balldebug: $(OUTPUT)runballDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

tabledebug: $(OUTPUT)runtableDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

threaddebug: $(OUTPUT)runthreadDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

solvedebug: $(OUTPUT)runsolveDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

handlerdebug: $(OUTPUT)runhandlerDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

initdebug: $(OUTPUT)runinitDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

skyboxdebug: $(OUTPUT)runskyboxDebug
	cd $(OUTPUT); ./finalDebug $(num_threads)

execute: $(OUTPUT)runMain
	cd $(OUTPUT); ./finalMain $(num_threads)

documentation: 
	cd latex_src/assign1_documentation && make -f Makefile1
changes:
	cd latex_src/assign1_changes && make -f Makefile2



clean:
	cd $(OBJECT); rm *;
	cd ..;
	cd $(OUTPUT); rm * ;
	

$(OUTPUT)runDebugger: $(OBJECT)gdbtable.o $(OBJECT)gdbskybox.o $(OBJECT)gdbrender.o $(OBJECT)gdbmenu.o $(OBJECT)gdbmain.o $(OBJECT)gdbinitialisation.o $(OBJECT)gdbhandler.o $(OBJECT)gdbequationSolver.o $(OBJECT)gdbballThreads.o $(OBJECT)gdbball.o
	$(COMPILE) $(CFLAGS) -g  $(OBJECT)gdbtable.o $(OBJECT)gdbskybox.o $(OBJECT)gdbrender.o $(OBJECT)gdbmenu.o $(OBJECT)gdbmain.o $(OBJECT)gdbinitialisation.o $(OBJECT)gdbhandler.o $(OBJECT)gdbequationSolver.o $(OBJECT)gdbballThreads.o $(OBJECT)gdbball.o -o finalDebugger $(LIBRARIES) 
	mv finalDebugger $(OUTPUT)finalDebugger

$(OUTPUT)runDebug: $(OBJECT)mdtable.o $(OBJECT)mdskybox.o $(OBJECT)mdrender.o $(OBJECT)mdmenu.o $(OBJECT)mdmain.o $(OBJECT)mdinitialisation.o $(OBJECT)mdhandler.o $(OBJECT)mdequationSolver.o $(OBJECT)mdballThreads.o $(OBJECT)mdball.o
	$(COMPILE) $(Debug) $(CFLAGS)  $(OBJECT)mdtable.o $(OBJECT)mdskybox.o $(OBJECT)mdrender.o $(OBJECT)mdmenu.o $(OBJECT)mdmain.o $(OBJECT)mdinitialisation.o $(OBJECT)mdhandler.o $(OBJECT)mdequationSolver.o $(OBJECT)mdballThreads.o $(OBJECT)mdball.o -o finalDebug $(LIBRARIES) 
	mv finalDebug $(OUTPUT)finalDebug

$(OUTPUT)runballDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)sdball.o
	$(COMPILE) $(ballDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)sdball.o -o finalballDebug $(LIBRARIES) 
	mv finalballDebug $(OUTPUT)finalballDebug

$(OUTPUT)runtableDebug: $(OBJECT)sdtable.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(tableDebug) $(CFLAGS)  $(OBJECT)sdtable.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finaltableDebug $(LIBRARIES) 
	mv finaltableDebug $(OUTPUT)finaltableDebug

$(OUTPUT)runthreadDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)sdballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(threadDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)sdballThreads.o $(OBJECT)ball.o -o finalthreadDebug $(LIBRARIES) 
	mv finalthreadDebug $(OUTPUT)finalthreadDebug

#No solve debug

$(OUTPUT)runhandlerDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)sdhandler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(handlerDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)sdhandler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalhandlerDebug $(LIBRARIES) 
	mv finalhandlerDebug $(OUTPUT)finalhandlerDebug

$(OUTPUT)runinitDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)sdinitialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(initDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)sdinitialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalinitDebug $(LIBRARIES) 
	mv finalinitDebug $(OUTPUT)finalinitDebug

$(OUTPUT)runskyboxDebug: $(OBJECT)table.o $(OBJECT)sdskybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(skyboxDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)sdskybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalskyboxDebug $(LIBRARIES) 
	mv finalskyboxDebug $(OUTPUT)finalskyboxDebug




$(OUTPUT)runMain: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalMain $(LIBRARIES) 
	mv finalMain $(OUTPUT)finalMain

###############################################

$(OBJECT)ball.o: $(SOURCE)ball.cpp $(SOURCE)ball.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)ball.cpp -o ball.o $(LIBRARIES)
	mv ball.o $(OBJECT)ball.o

$(OBJECT)gdbball.o: $(SOURCE)ball.cpp $(SOURCE)ball.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)ball.cpp -o gdbball.o $(LIBRARIES)
	mv gdbball.o $(OBJECT)gdbball.o

$(OBJECT)mdball.o: $(SOURCE)ball.cpp $(SOURCE)ball.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)ball.cpp -o mdball.o $(LIBRARIES)
	mv mdball.o $(OBJECT)mdball.o

$(OBJECT)sdball.o: $(SOURCE)ball.cpp $(SOURCE)ball.h
	$(COMPILE) $(ballDebug) $(CFLAGS) -c $(SOURCE)ball.cpp -o sdball.o $(LIBRARIES)
	mv sdball.o $(OBJECT)sdball.o

###############################################

$(OBJECT)ballThreads.o: $(SOURCE)ballThreads.cpp $(SOURCE)ballThreads.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)ballThreads.cpp -o ballThreads.o $(LIBRARIES)
	mv ballThreads.o $(OBJECT)ballThreads.o

$(OBJECT)gdbballThreads.o: $(SOURCE)ballThreads.cpp $(SOURCE)ballThreads.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)ballThreads.cpp -o gdbballThreads.o $(LIBRARIES)
	mv gdbballThreads.o $(OBJECT)gdbballThreads.o

$(OBJECT)mdballThreads.o: $(SOURCE)ballThreads.cpp $(SOURCE)ballThreads.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)ballThreads.cpp -o mdballThreads.o $(LIBRARIES)
	mv mdballThreads.o $(OBJECT)mdballThreads.o

$(OBJECT)sdballThreads.o: $(SOURCE)ballThreads.cpp $(SOURCE)ballThreads.h
	$(COMPILE) $(threadDebug) $(CFLAGS) -c $(SOURCE)ballThreads.cpp -o sdballThreads.o $(LIBRARIES)
	mv sdballThreads.o $(OBJECT)sdballThreads.o
###############################################

$(OBJECT)equationSolver.o: $(SOURCE)equationSolver.cpp $(SOURCE)equationSolver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)equationSolver.cpp -o equationSolver.o $(LIBRARIES)
	mv equationSolver.o $(OBJECT)equationSolver.o


$(OBJECT)gdbequationSolver.o: $(SOURCE)equationSolver.cpp $(SOURCE)equationSolver.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)equationSolver.cpp -o gdbequationSolver.o $(LIBRARIES)
	mv gdbequationSolver.o $(OBJECT)gdbequationSolver.o

$(OBJECT)mdequationSolver.o: $(SOURCE)equationSolver.cpp $(SOURCE)equationSolver.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)equationSolver.cpp -o mdequationSolver.o $(LIBRARIES)
	mv mdequationSolver.o $(OBJECT)mdequationSolver.o

#No cout statements.

################################################

$(OBJECT)handler.o: $(SOURCE)handler.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)handler.cpp -o handler.o $(LIBRARIES)
	mv handler.o $(OBJECT)handler.o

	
$(OBJECT)gdbhandler.o: $(SOURCE)handler.cpp $(SOURCE)screenSaver.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)handler.cpp -o gdbhandler.o $(LIBRARIES)
	mv gdbhandler.o $(OBJECT)gdbhandler.o

	
$(OBJECT)mdhandler.o: $(SOURCE)handler.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)handler.cpp -o mdhandler.o $(LIBRARIES)
	mv mdhandler.o $(OBJECT)mdhandler.o

	
$(OBJECT)sdhandler.o: $(SOURCE)handler.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(handlerDebug) $(CFLAGS) -c $(SOURCE)handler.cpp -o sdhandler.o $(LIBRARIES)
	mv sdhandler.o $(OBJECT)sdhandler.o
###############################################


$(OBJECT)initialisation.o: $(SOURCE)initialisation.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)initialisation.cpp -o initialisation.o $(LIBRARIES)
	mv initialisation.o $(OBJECT)initialisation.o


$(OBJECT)gdbinitialisation.o: $(SOURCE)initialisation.cpp $(SOURCE)screenSaver.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)initialisation.cpp -o gdbinitialisation.o $(LIBRARIES)
	mv gdbinitialisation.o $(OBJECT)gdbinitialisation.o


$(OBJECT)mdinitialisation.o: $(SOURCE)initialisation.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)initialisation.cpp -o mdinitialisation.o $(LIBRARIES)
	mv mdinitialisation.o $(OBJECT)mdinitialisation.o


$(OBJECT)sdinitialisation.o: $(SOURCE)initialisation.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(initDebug) $(CFLAGS) -c $(SOURCE)initialisation.cpp -o sdinitialisation.o $(LIBRARIES)
	mv sdinitialisation.o $(OBJECT)sdinitialisation.o

###############################################
$(OBJECT)main.o: $(SOURCE)main.cpp $(SOURCE)includes.h $(SOURCE)screenSaver.h $(SOURCE)ball.h $(SOURCE)table.h $(SOURCE)ballThreads.h $(SOURCE)skybox.h $(SOURCE)menu.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)main.cpp -o main.o $(LIBRARIES)
	mv main.o $(OBJECT)main.o

$(OBJECT)gdbmain.o: $(SOURCE)main.cpp $(SOURCE)includes.h $(SOURCE)screenSaver.h $(SOURCE)ball.h $(SOURCE)table.h $(SOURCE)ballThreads.h $(SOURCE)skybox.h $(SOURCE)menu.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)main.cpp -o gdbmain.o $(LIBRARIES)
	mv gdbmain.o $(OBJECT)gdbmain.o

$(OBJECT)mdmain.o: $(SOURCE)main.cpp $(SOURCE)includes.h $(SOURCE)screenSaver.h $(SOURCE)ball.h $(SOURCE)table.h $(SOURCE)ballThreads.h $(SOURCE)skybox.h $(SOURCE)menu.h
	$(COMPILE) $(Debug) -g $(CFLAGS) -c $(SOURCE)main.cpp -o mdmain.o $(LIBRARIES)
	mv mdmain.o $(OBJECT)mdmain.o

#NO MAIN DEBUG - actually. wait.

###############################################
$(OBJECT)menu.o: $(SOURCE)menu.cpp $(SOURCE)menu.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)menu.cpp -o menu.o $(LIBRARIES)
	mv menu.o $(OBJECT)menu.o

$(OBJECT)gdbmenu.o: $(SOURCE)menu.cpp $(SOURCE)menu.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)menu.cpp -o gdbmenu.o $(LIBRARIES)
	mv gdbmenu.o $(OBJECT)gdbmenu.o

$(OBJECT)mdmenu.o: $(SOURCE)menu.cpp $(SOURCE)menu.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)menu.cpp -o mdmenu.o $(LIBRARIES)
	mv mdmenu.o $(OBJECT)mdmenu.o

$(OBJECT)sdmenu.o: $(SOURCE)menu.cpp $(SOURCE)menu.h
	$(COMPILE) $(menuDebug) $(CFLAGS) -c $(SOURCE)menu.cpp -o sdmenu.o $(LIBRARIES)
	mv sdmenu.o $(OBJECT)sdmenu.o



###############################################
$(OBJECT)render.o: $(SOURCE)render.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)render.cpp -o render.o $(LIBRARIES)
	mv render.o $(OBJECT)render.o

$(OBJECT)gdbrender.o: $(SOURCE)render.cpp $(SOURCE)screenSaver.h
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)render.cpp -o gdbrender.o $(LIBRARIES)
	mv gdbrender.o $(OBJECT)gdbrender.o

$(OBJECT)mdrender.o: $(SOURCE)render.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)render.cpp -o mdrender.o $(LIBRARIES)
	mv mdrender.o $(OBJECT)mdrender.o

#NO RENDER DEBUG

###############################################
$(OBJECT)skybox.o: $(SOURCE)skybox.cpp $(SOURCE)skybox.h 
	$(COMPILE) $(CFLAGS) -c $(SOURCE)skybox.cpp -o skybox.o $(LIBRARIES)
	mv skybox.o $(OBJECT)skybox.o

$(OBJECT)gdbskybox.o: $(SOURCE)skybox.cpp $(SOURCE)skybox.h 
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)skybox.cpp -o gdbskybox.o $(LIBRARIES)
	mv gdbskybox.o $(OBJECT)gdbskybox.o

$(OBJECT)mdskybox.o: $(SOURCE)skybox.cpp $(SOURCE)skybox.h 
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)skybox.cpp -o mdskybox.o $(LIBRARIES)
	mv mdskybox.o $(OBJECT)mdskybox.o

$(OBJECT)sdskybox.o: $(SOURCE)skybox.cpp $(SOURCE)skybox.h 
	$(COMPILE) $(skyboxDebug) $(CFLAGS) -c $(SOURCE)skybox.cpp -o sdskybox.o $(LIBRARIES)
	mv sdskybox.o $(OBJECT)sdskybox.o

###############################################
$(OBJECT)table.o: $(SOURCE)table.cpp $(SOURCE)table.h 
	$(COMPILE) $(CFLAGS) -c $(SOURCE)table.cpp -o table.o $(LIBRARIES)
	mv table.o $(OBJECT)table.o

$(OBJECT)gdbtable.o: $(SOURCE)table.cpp $(SOURCE)table.h 
	$(COMPILE) -g $(CFLAGS) -c $(SOURCE)table.cpp -o gdbtable.o $(LIBRARIES)
	mv gdbtable.o $(OBJECT)gdbtable.o

$(OBJECT)mdtable.o: $(SOURCE)table.cpp $(SOURCE)table.h 
	$(COMPILE) $(Debug) $(CFLAGS) -c $(SOURCE)table.cpp -o mdtable.o $(LIBRARIES)
	mv mdtable.o $(OBJECT)mdtable.o

$(OBJECT)sdtable.o: $(SOURCE)table.cpp $(SOURCE)table.h 
	$(COMPILE) $(tableDebug) $(CFLAGS) -c $(SOURCE)table.cpp -o sdtable.o $(LIBRARIES)
	mv sdtable.o $(OBJECT)sdtable.o

###############################################