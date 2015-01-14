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

		vector<float> getBottomLeftCorner() { return corners[0]; }
		vector<float> getBottomRightCorner() { return corners[1]; }
		vector<float> getTopRightCorner() { return corners[2]; }
		vector<float> getTopLeftCorner() { return corners[3]; }
		void setCorners(vector< vector<float> > _newCorners) { corners = _newCorners; }

		void display();
		void reshape( int w , int h , int oldWidth , int oldHeight);
};

#endif
