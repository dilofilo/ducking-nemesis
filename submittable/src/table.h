#ifndef TABLE_H
	#define TABLE_H

#include "includes.h"

///A class that handles the box/table of the screenSaver.
class Table {
	private:
		vector< vector<float> > corners;
		vector<float> color;
		float myColour[4];
	///Corners are assumed to start at the "BOTTOMLEFT" and rotate counterclockwise to the "TOPLEFT"
	public:	
		Table(vector< vector<float> > _corners , vector<float> _color ) {
			corners = _corners;
			color = _color;
				myColour[3] = 1.0;
				myColour[0] =color[0];
				myColour[1] =color[1];
				myColour[2] =color[2];
		} //Constructor that accepts color, corners
		~Table() {
			//delete[] myColour;
		}

		//Get and set functions
		vector<float> getBottomLeftFrontCorner() { return corners[0]; }
		vector<float> getBottomRightFrontCorner() { return corners[1]; }
		vector<float> getTopRightFrontCorner() { return corners[2]; }
		vector<float> getTopLeftFrontCorner() { return corners[3]; }
		vector<float> getBottomLeftBackCorner() { return corners[4]; }
		vector<float> getBottomRightBackCorner() { return corners[5]; }
		vector<float> getTopRightBackCorner() { return corners[6]; }
		vector<float> getTopLeftBackCorner() { return corners[7]; }
		void setCorners(vector< vector<float> > _newCorners) { corners = _newCorners; }

		//deprecated
		void randomizeColor();

		//Called by screenSavers display to display box/table
		void display();		
			void drawEdges();
			void drawCrosses();
			void translucentWalls();
			void drawSurface();
			void solveLighting();
		//Called upon resizing of the window.
		void reshape( int w , int h , int oldWidth , int oldHeight);
};

///Global Variable used by the entire program.

#endif
