########################################################################################
Made by :   Kabeer Chhabra   Haroun Habeeb    Harman Kumar
########################################################################################

########################################################################################
Introduction :
########################################################################################

	The purpose of this assignment is to create an interactive screensaver with balls moving in 2D or 3D space using one to one thread communication model
	such that there is a thread controlling a single ball. Additional features like selection of a ball using mouse click, enable gravity, change the viewing mode etc. 
	were also incorporated.

	For guidelines to compile the project, refer to compilation and execution modes section.
	
	Acknowledgements :

		We'd like to thank "Barun Patra", Akshay Gupta, Kartikeya Gupta, Prateek, Venkata Raman, Nikhil Chaturvedi for helping us understand various concepts, libraries.



########################################################################################
Requirements :
########################################################################################


	The libraries required for compilation of the project are : 
		1. openGL
		2. glut or freeglut
		3. SDL
		4. glui
		5. pthread

	The version of g++ required to compile the project is the c++11 version.

########################################################################################
Compilation and Execution Modes:
########################################################################################

	Compiling the Documentation :

		"make documentation" in the Assignment's folder to compile the .tex file and give a .pdf file corresponding to the documentation.

		"make changes" in the Assignment's folder to compile the .tex file and give a .pdf file corresponding to the changes made.

	Compiling the Project :

		The compilation modes and associated syntax are:

		"make execute num_threads=n" : 		Launches the program in 2D mode. 

		"make clean" :  			   		Removes all the .o (object) and .out (executable) files. 

		"make debugger" : 			   		Creates a gdb-supported executable executable file.

		"make debug num_threads=n" : 		Launches an executable with output statements.	

		"make balldebug num_threads=n" :	Launches an executable with output statements in ball.cpp.

		"make initdebug num_threads=n" 	:	Launches an executable with output statements in init.cpp.

		"make skyboxdebug num_threads=n" :	Launches an executable with output statements in skybox.cpp.

		"make tabledebug num_threads=n" :	Launches an executable with output statements in table.cpp.

		"make threaddebug num_threads=n" :	Launches an executable with output statements in thread.cpp.

		"make solvedebug num_threads=n"	:	Launches an executable with output statements in solve.cpp.

		"make handlerdebug num_threads=n" :	Launches an executable with output statements in handler.cpp.



########################################################################################
User Interface :
########################################################################################

	1. GUI (Graphical User Interface)
	
	The user is provided with a menu to perform the following operations on the screensaver.
		Rotate the view of the cube : The user can change the location from where the cube ( in which the balls are contained ) 
		is being viewed, also an option to zoom-in and zoom-out is provided.

		Toggle between 2D and 3D modes : The user can switch between 2D and 3D modes during the execution of the screensaver.

		Add Gravity and Coefficient of Restitution : There is a button that toggles the gravity and introduces a coefficient of restitution on collision between a ball and the wall.
 
 		Velocity Control : There are buttons to increase/decrease the velocity of the selected ball.
	
		Select the next/previous ball : There are buttons that enable the user to select the next and the prevois ball.
		
		Change the ball's resolution : There are three modes among which the user can switch during the execution of the screensaver.
 		
 		Pause and Exit : There is a button to pause the screensaver and another button to close the window.

		Fullscreen : There is a button to make the window fullscreen.

 	2. Keyboard

	The keyboard can be used as an alternative to the GUI to perform operations on the screen-saver.
		
		1. Rotate the view of the cube : The keys w, a, s, d, q, e can be used to rotate the cube and hence change the view, following are the functionalities:

 			a) To rotate about the X axis the keys w and s are to be used.
 			b) To rotate about the Y axis the keys q and e are to be used.
 			c) To rotate about the Z axis the keys a and d are to be used.

		2. Change the selected ball : Using the left and right arrow keys one can change the ball that is selected.
		
		3. Velocity control : Using the up and down arrow keys one can increase/decrease the velocity of the selected ball.
	
		4. Pause and Exit : The screensaver can be paused by pressing spacebar and closed by pressing escape.
	
		5. Fullscreen : The window can be made fullscreen by pressing the f key.
		
		6. Change colour of a ball : The colour of the selected can be changed by pressing the 'c' key.

	3. Mouse
 
		 Left Mouse Button Click : The left mouse button can be used to select a ball on the screen. In case of overlap btween balls ( in 3D mode ) priority is given to the closer ball.
 
		 Roll : The user can zoom-in an zoom-out by rolling up and rolling down respectively.
 
		 Right Mouse Button Click : Deselection of balls happens when the right mouse button is pressed i.e. after the click of this button no ball on the screen remains selected.


########################################################################################
Bibliography :
########################################################################################

		1) OpenGL documentation. 
		2) Threading Guide : http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
		3) Physics and equations of motion : Wolfram Alpha
		4) GLUI Manual : https://www.cs.unc.edu/~rademach/glui/src/release/glui_manual_v2_beta.pdf 
		5) NeHe tutorials
		6) Lighthouse3D.com
		7) Youtube Video tutorials.
########################################################################################