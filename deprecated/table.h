#ifndef TABLE_H
	#define TABLE_H
#include <GL/glut.h>

class Table{
	private:
		float xll,yll , xlr,ylr , xtr,ytr , xtl,ytl , z;
		float oldWidth,oldHeight;
		float color[4];
	public:
		Table( float _xll,float _yll , float _xlr,float _ylr , float _xtr,float _ytr , float _xtl,float _ytl , float _z , float R , float G , float B , float _oldWidth , float _oldHeight) {
			xll = _xll;
			yll = _yll;

			xlr = _xlr;
			ylr = _ylr;

			xtr = _xtr;
			ytr = _ytr;

			xtl = _xtl;
			ytl = _ytl;

			z = _z ;
			
			color[0] = R;
			color[1] = G;
			color[2] = B;
			color[3] = 1.0;

			oldWidth = _oldWidth;
			oldHeight = _oldHeight;
		} //Constructor complete.
		~Table();
		
		//SET and GET functions
		void setxll(float _xll) { xll = _xll; }
		void setyll(float _yll) { yll = _yll; }
		void setxlr(float _xlr) { xlr = _xlr; }
		void setylr(float _ylr) { ylr = _ylr; }
		void setxtr(float _xtr) { xtr = _xtr; }
		void setytr(float _ytr) { ytr = _ytr; }
		void setxtl(float _xtl) { xtl = _xtl; }
		void setytl(float _ytl) { ytl = _ytl; }

		float getxll() { return xll; }
		float getyll() { return yll; }
		float getxlr() { return xlr; }
		float getylr() { return ylr; }
		float getxtr() { return xtr; }
		float getytr() { return ytr; }
		float getxtl() { return xtl; }
		float getytl() { return ytl; }

		void reshape(int w , int h); ///function to handle reshaping of table
		void display(); /// function to handle displaying the table
		void print();
};

#endif