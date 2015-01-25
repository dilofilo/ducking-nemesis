#Directories
OUTPUT=output/
OBJECT=obj/
SOURCE=src/

#Compiler Variables
COMPILE=g++ -std=c++11
CFLAGS=-w
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

#Document Generation


#make file modes
debugger: $(OUTPUT)runDebugger
	cd $(OUTPUT); ./runDebugger $(num_threads) 
	  
debug: $(OUTPUT)runDebug
	cd $(OUTPUT); ./runDebug $(num_threads)	> log.txt

balldebug: $(OUTPUT)runballDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

tabledebug: $(OUTPUT)runtableDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

threaddebug: $(OUTPUT)runthreadDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

solvedebug: $(OUTPUT)runsolveDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

handlerdebug: $(OUTPUT)runhandlerDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

initdebug: $(OUTPUT)runinitDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

skyboxdebug: $(OUTPUT)runskyboxDebug
	cd $(OUTPUT); ./runDebug $(num_threads) > log.txt

execute: $(OUTPUT)runMain
	cd $(OUTPUT); ./runMain $(num_threads)

documentation: 
	cd latex_src && make -f Makefile1
	make -f Makefile2 



clean:	$(OUTPUT)runClean
	cd $(OUTPUT); 
	

$(OUTPUT)runDebugger: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(CFLAGS) -g  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalDebugger $(LIBRARIES) 
	mv finalDebugger $(OUTPUT)finalDebugger
$(OUTPUT)runDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(Debug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalDebug $(LIBRARIES) 
	mv finalDebug $(OUTPUT)finalDebug
$(OUTPUT)runballDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(ballDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalballDebug $(LIBRARIES) 
	mv finalballDebug $(OUTPUT)finalballDebug
$(OUTPUT)runtableDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(tableDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finaltableDebug $(LIBRARIES) 
	mv finaltableDebug $(OUTPUT)finaltableDebug
$(OUTPUT)runthreadDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(threadDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalthreadDebug $(LIBRARIES) 
	mv finalthreadDebug $(OUTPUT)finalthreadDebug
$(OUTPUT)runsolveDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(solveDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalsolveDebug $(LIBRARIES) 
	mv finalsolveDebug $(OUTPUT)finalsolveDebug
$(OUTPUT)runhandlerDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(handlerDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalhandlerDebug $(LIBRARIES) 
	mv finalhandlerDebug $(OUTPUT)finalhandlerDebug
$(OUTPUT)runinitDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(initDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalinitDebug $(LIBRARIES) 
	mv finalinitDebug $(OUTPUT)finalinitDebug
$(OUTPUT)runskyboxDebug: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(skyboxDebug) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalskyboxDebug $(LIBRARIES) 
	mv finalskyboxDebug $(OUTPUT)finalskyboxDebug




$(OUTPUT)runMain: $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o
	$(COMPILE) $(CFLAGS)  $(OBJECT)table.o $(OBJECT)skybox.o $(OBJECT)render.o $(OBJECT)menu.o $(OBJECT)main.o $(OBJECT)initialisation.o $(OBJECT)handler.o $(OBJECT)equationSolver.o $(OBJECT)ballThreads.o $(OBJECT)ball.o -o finalMain $(LIBRARIES) 
	mv finalMain $(OUTPUT)finalMain

$(OBJECT)ball.o: $(SOURCE)ball.cpp $(SOURCE)ball.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)ball.cpp -o ball.o $(LIBRARIES)
	mv ball.o $(OBJECT)ball.o
$(OBJECT)ballThreads.o: $(SOURCE)ballThreads.cpp $(SOURCE)ballThreads.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)ballThreads.cpp -o ballThreads.o $(LIBRARIES)
	mv ballThreads.o $(OBJECT)ballThreads.o
$(OBJECT)equationSolver.o: $(SOURCE)equationSolver.cpp $(SOURCE)equationSolver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)equationSolver.cpp -o equationSolver.o $(LIBRARIES)
	mv equationSolver.o $(OBJECT)equationSolver.o
$(OBJECT)handler.o: $(SOURCE)handler.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)handler.cpp -o handler.o $(LIBRARIES)
	mv handler.o $(OBJECT)handler.o
$(OBJECT)initialisation.o: $(SOURCE)initialisation.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)initialisation.cpp -o initialisation.o $(LIBRARIES)
	mv initialisation.o $(OBJECT)initialisation.o
$(OBJECT)main.o: $(SOURCE)main.cpp $(SOURCE)includes.h $(SOURCE)screenSaver.h $(SOURCE)ball.h $(SOURCE)table.h $(SOURCE)ballThreads.h $(SOURCE)skybox.h $(SOURCE)menu.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)main.cpp -o main.o $(LIBRARIES)
	mv main.o $(OBJECT)main.o
$(OBJECT)menu.o: $(SOURCE)menu.cpp $(SOURCE)menu.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)menu.cpp -o menu.o $(LIBRARIES)
	mv menu.o $(OBJECT)menu.o
$(OBJECT)render.o: $(SOURCE)render.cpp $(SOURCE)screenSaver.h
	$(COMPILE) $(CFLAGS) -c $(SOURCE)render.cpp -o render.o $(LIBRARIES)
	mv render.o $(OBJECT)render.o
$(OBJECT)skybox.o: $(SOURCE)skybox.cpp $(SOURCE)skybox.h 
	$(COMPILE) $(CFLAGS) -c $(SOURCE)skybox.cpp -o skybox.o $(LIBRARIES)
	mv skybox.o $(OBJECT)skybox.o
$(OBJECT)table.o: $(SOURCE)table.cpp $(SOURCE)table.h 
	$(COMPILE) $(CFLAGS) -c $(SOURCE)table.cpp -o table.o $(LIBRARIES)
	mv table.o $(OBJECT)table.o
