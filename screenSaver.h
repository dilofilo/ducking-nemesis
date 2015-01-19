//glut stuff
static int WIDTH;
static int HEIGHT;
static int DELTA_T;
//program specific stuff
static int NUM_BALLS;
static int Z_CAMERA;

class ScreenSaver {
public:
	ScreenSaver(int numBalls);
	~ScreenSaver();
	
	///Initializes the table and the balls.
	void init();

	///Called to start.
	void execute();
	

	///Control functions
	void display();
	void reshape(int w , int h);
	void timer(int value);

	///User I/O function
	void handleMouse(int button , int state , int x , int y);
	void handleKeyboard(unsigned char key , int x , int y);
	void handleSpecialKey(unsigned char key , int x , int y);
};