//Help was received in this code from Adam Rasfeld, and Jason Weber (both in CSE274, but different sections)

//Many of these include files are not necessary, but they were used when trying to implement my K-D Tree
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "cinder/Text.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/app/KeyEvent.h"
#include <vector>
#include "Resources.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>
#include <ios>
#include <istream>

#include "Starbucks.h"
#include "beilcaStarbucks.h"

/*
I was absolutely correct in my assumption that my K-D Tree would be an 8 on the difficulty scale to build.
Since starting this project I have realized I just do not understand c++/cinder and its syntax as much as
I need in order to complete this project to the best of my ability. Through hours of video tutorials and 
other tutorials on www.cplusplus.com I am still stuck in a rut, and now it has put me a day behind.

For part 2, I understand it is late, and I also did not follow through with my K-D tree, and thus will 
suffer a harsh grade penalty, with which I am not proud of in the least. I will have to suck it up and just 
build an array, and sort through the items in a list. I better be dead accurate. 
*/

//Big thanks for help from Adam Rasfeld on the tasks that I did manage to accomplish on this assignment.

//Using reference and tutorials for i/o streams
//http://cplusplus.com/reference/iostream/

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_beilcaApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	beilcaStarbucks* starbucks;
	int count;
	int census2000count;
	int census2010count;
	void update();
	Entry* data;
	Entry* census2000;
	Entry* census2010;
	void draw();
	Entry* nearestStarbucks;
	void prepareSettings(Settings* settings);
	static const int kAppWidth = 800; 
	static const int kAppHeight = 600;
	static const int kTextureSize = 1024;
	bool drawStarbucks;
	Surface* mySurface_;

};

void HW04_beilcaApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void HW04_beilcaApp::setup(){
	drawStarbucks = true;
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
/*	Since part 1 of this assignment doesn't include graphics, we can do all of our coding inside the
	setup, and just work with 'cin' and 'cout' for input and output to and from the console with our
	current test results.
*/

//First off I need to get the data from "Starbucks_2006.csv" and put that data into an array

	ifstream inStream("../resources/Starbucks_2006.csv");

	string line;
	double x, y;
	
	count = 0;
	census2000count = 0;
	census2010count = 0;
	//Variable to keep track of how many numbers are in the list, to then be able to build
	//an array of 'count' length
	
	//This will not work in cinder
	//cout << "Count is: " << count << endl;

	while(inStream.good()){
		//To get each line's identifier, x value, and y value
		getline(inStream, line, ',');
		inStream >> x;
		inStream.get();
		inStream >> y;
		inStream.get();
		count++;
	}


	//This will not work in cinder
	//cout << "Count is: " << count << endl;

	//Restart the input stream at the beginning
	inStream.close();
	inStream.open("../resources/Starbucks_2006.csv");

	//Declare a new pointer to an array of length 'count'


	//*****************************************************************************
	//Here is where I got rid of "Entry* "
	data = new Entry[count];

	int i = 0;
	while(inStream.good()) {
		getline(inStream, line, ',');
        inStream >> x;
        inStream.get();
        inStream >> y;
        inStream.get();
        (data+i)->identifier = line;
        (data+i)->x = x;
        (data+i)->y = y;
        i++;
	}

	//My for loop is broken
	/*
	for (int i = 0; i < count; i++){
		//To get each line's identifier, x value, and y value
		Entry entry;
		getline(inStream, line, ',');
		data[i].identifier = line;
		
		//Have the current node get the x value stored in the document
		inStream.get();
		//data[i].x = line will not work because you can't convert a string to a double
		inStream >> data[i].x;

		//Have the current node get the y value stored in the document
		inStream.get();
		//Similarly data[i].y = line will not work because you can't convert a string to a double
		inStream >> data[i].y;
	}
	*/
	
	//close the input stream and delete the 
	inStream.close();

	//create a beilcaStarbucks and build a regular array...(tried K-D many times with 0 success)
	starbucks = new beilcaStarbucks();
	starbucks->build(data, count);
	nearestStarbucks = data;


	ifstream census2000stream("../resources/Census_2000.csv");
	
	census2000count = 0;
	//Variable to keep track of how many numbers are in the list, to then be able to build
	//an array of 'count' length
	
	//This will not work in cinder
	//cout << "Count is: " << count << endl;

	while(census2000stream.good()){
		//To get each line's identifier, x value, and y value
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000count++;
	}

	census2000 = new Entry[census2000count];
	i = 0;

	while(census2000stream.good()){
		//To get each line's identifier, x value, and y value
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream.get();
		census2000stream >> x;
		census2000stream.get();
		census2000stream >> y;
		census2000stream.get();
		census2000count++;
		(census2000+i)->x = x;
        (census2000+i)->y = y;
        i++;
	}

	//I've tried over and over to read in the data to have it be an applicable number for x and y
	//using the equations you gave us in the email, but nothing seemed to work for me.

	//Hoping this assignment is graded on effort as well :/
	HW04_beilcaApp::console() << "Census Line 1: " << census2000->x << std::endl;
	HW04_beilcaApp::console() << "Census Line 1: " << census2000->y << std::endl;
}

void HW04_beilcaApp::mouseDown( MouseEvent event ){


	//Help with getting the right x and y values from Jason Weber (weberjt)
	if(event.isLeftDown()){
		//Nearly Satisfies Goal B which is to visually show which Starbucks is the closest.
		//It doesn't work perfectly, but it shows a different result everytime.
		//The call to draw the nearestStarbucks is down in the draw function
		double x = abs((event.getX() - 50) / 700.0);
		double y = abs(1 - ((event.getY()) / 525.0));
		nearestStarbucks = starbucks->getNearest(x, y);
		gl::color(Color8u(0, 255, 0));
		HW04_beilcaApp::console() << "Closest Starbucks is located here: " << nearestStarbucks->identifier << std::endl;
	}

	if(event.isRightDown()){
		drawStarbucks = !drawStarbucks;
	}

	/*
	//ZOOM FUNCTION!...not working

	if(event.isShiftDown() && event.isRightDown()){
		for(int i = 0; i < count; i++){
			data[i].x += event.getX()/3;
			data[i].y += event.getY()/3;
		}
	}

	if(event.isShiftDown() && event.isLeftDown()){

		for(int i = 0; i < count; i++){
			data[i].x += event.getX()/3;
			data[i].y += event.getY()/3;
		}
	}
	*/
}

void HW04_beilcaApp::update()
{

}

void HW04_beilcaApp::draw()
{
	//Still nothing works, Learning Cinder on top of C++ in an environment to which I am unfamiliar is not fun
	//Visual Studio/Cinder sucks at providing you any helpful error messages when your program does not work...

	//gl::drawString	("hello", Vec2f & (0,0,0,0), ColorA & 	color = ColorA( 1, 1, 1, 1 ), Font 	font = Font());	

	gl::clear(Color8u(0,0,0));
	gl::color(Color8u(200,200,200));
	gl::drawSolidRect(Rectf(20,20, kAppWidth-20, kAppHeight-20));
	


	if(drawStarbucks){
		//This satisfies HW04Phase02 Basic Goal A- 20 pts
		gl::color(Color8u(255, 0, 0));
		for (int i = 0; i < count; i++){

			//The understanding of Vec2f and how to draw things using "gl::" was from Jason Weber (weberjt)
			gl::drawSolidCircle(Vec2f((data[i].x * 700 + 50), 600-(data[i].y * 525 + 50)), 2);
		}
		//When I draw this, my nearestStarbucks seems to be a bit off!
		gl::color(Color8u(0,255,0));
		gl::drawSolidCircle(Vec2f((nearestStarbucks->x * 700) + 50, 550- (nearestStarbucks->y * 600)), 3);
	}
	
	if(!drawStarbucks){

	}
}

CINDER_APP_BASIC( HW04_beilcaApp, RendererGl )
