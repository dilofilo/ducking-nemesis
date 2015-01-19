#ifndef TABLE_H
	#define TABLE_H

vector<float> vecUnity{ 1.0 , 1.0 , 1.0};
class Table {
	private:
		vector< vector<float> > corners;
		vector<float> color;

	///Corners are assumed to start at the "BOTTOMLEFT" and rotate counterclockwise to the "TOPLEFT"
	public:	
		Table(vector< vector<float> > _corners , vector<float> _color = vecUnity ) {
			corners = _corners;
			color = _color;
		}
		~Table();

		vector<float> getBottomLeftFrontCorner() { return corners[0]; }
		vector<float> getBottomRightFrontCorner() { return corners[1]; }
		vector<float> getTopRightFrontCorner() { return corners[2]; }
		vector<float> getTopLeftFrontCorner() { return corners[3]; }
		vector<float> getBottomLeftBackCorner() { return corners[4]; }
		vector<float> getBottomRightBackCorner() { return corners[5]; }
		vector<float> getTopRightBackCorner() { return corners[6]; }
		vector<float> getTopLeftBackCorner() { return corners[7]; }
		void setCorners(vector< vector<float> > _newCorners) { corners = _newCorners; }

		void display();
		void reshape( int w , int h , int oldWidth , int oldHeight);
};

#endif
