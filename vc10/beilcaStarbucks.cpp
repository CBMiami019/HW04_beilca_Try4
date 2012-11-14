/*	Author:	Carter Beil
	Date:	October 20, 2012
	File: beilcaStarbucks.cpp
*/

#include "Starbucks.h"
#include "beilcaStarbucks.h"

using namespace ci;
/*Node::Node(){
	left_ = right_ = NULL;
	data = new Entry();			
}
*/

//Constructor
beilcaStarbucks::beilcaStarbucks(){
	color = Color(Rand::randFloat(), Rand::randFloat(), Rand::randFloat());
}

//beilcaStarbucks::beilcaStarbucks(Entry* e){
	//this->entry = data;
	//this-> = NULL;
	//this->right = NULL;
//}

 /*
 * add all entries in the array to your data structure
 *
 * The "c" parameter is a pointer to an array of all the entries to be added, and n is the length of
 * the array.
 *
 * Note: If you detect that two items have the same coordinates, then do not add the new item
 *       that has the same coordinates as another item. This is guaranteed to happen, by the way,
 *       because some Starbucks locations are listed in the database twice. We will define two locations
 *       to be the "same location" if both |x1 - x2| <= 0.00001 and |y1 - y2| < 0.00001
 */

//This was my K-D Build method, cannot get it to work.
 /*void beilcaStarbucks::build(Entry* e, Node* r, int count){
	 randomize(e, count);
	 Entry* root = &e[0];

	 Entry* build = new Entry [count];
	 
	 for (int i = 0; i< count; i++){
			insert((e+i), , true);
	 }
 }

*/

void beilcaStarbucks::build(Entry* e, int count){
	data = new Entry[count];
	arrayLength = count;

	/*for(int i = 0; i < arrayLength; i++){
		//Try to not add the same locations
		if(i >= 0 || i < (arrayLength-1)){
			//Check for repeated entries.
			if (abs(e[i-1].x-e[i].x) <= sameLocation && abs(e[i-1].y-e[i].y) <= sameLocation){
				//do nothing
			}else{
				data[i] = e[i];
			}
		}
	}*/

	for(int i = 0; i<arrayLength; i++){
		data[i] = e[i];
	}

	//Not necessary with a regular array of items, but would be useful when implementing a K-D tree
	//randomize(data, count);


}

/*
 //This was my K-D Insert Function, cannot get it to work.
 Node* beilcaStarbucks::insert(Entry* e, Node* r, bool xLevel) {
	 if (r->data == NULL) return;

	 if(e->x == r->data->x && e->y == r->data->y) return r;

	 if(xLevel){
		 if(e->x < r->data->x){
			 r->left_ = insert(e, r->left_, !xLevel);
		 }else{
			 r->right_ = insert(e, r->right_, !xLevel);
		 }
	 }else{
		 if(e->y < r->data->y){
			 r->left_ = insert(e, r->left_, !xLevel);
		 }else{
			 r->right_ = insert(e, r->right_, !xLevel);
		 }
	 }

	 return r;
}
*/

/*
* Return a pointer to the entry that is closest to the given coordinates. Your
*  answer may be approximate, but then you will lose points on the "Accuracy" quality measure
*/
Entry* beilcaStarbucks::getNearest(double x, double y){

	//I will implement the search function here, and probably just loop through
	// the data in the getNearest function

	//Call search to see if the values
	double shortestDistance = search(data[0], x, y);
	Entry* nearestStarbucks = &(data[0]);

	for(int i = 1; i < arrayLength; i++){
		double tempDistance = search(data[i], x, y);
		if (tempDistance < shortestDistance) {
			shortestDistance = tempDistance;
			nearestStarbucks = &(data[i]);
		}
	}
	return nearestStarbucks;
}

//Just calculates the distance between the given x and y values and those of the current entry's x and y vaules
double beilcaStarbucks::search(Entry e, double x, double y){ 
	if(x >1 || y>1){
		return 0;
	}else{
		double distance = (abs(sqrt(((e.x-x)*(e.x-x))+((e.y-y)*(e.y-y)))));
		return distance;
	}
}

//I would love to randomize my array before trying to build it!
//Helped from *uthnp*

void beilcaStarbucks::randomize(Entry* e, int arrayLength){
	int temp1 = 0;
	int temp2 = 0;
	Entry temp;

	for (int i = 0; i< arrayLength; i++){
			for (int i = 0; i < arrayLength; i++){
				//If the random numbers are the same, choose new ones until they are different
				while (temp1 == temp2){
					temp1 = (rand() % arrayLength);
					temp2 = (rand() % arrayLength);
				}
			//Switch the values of the temp values with the ones in the array, to scramble it
			temp = e[temp1];
			e[temp1] = e[temp2];
			e[temp2] = temp;
		}
	}
}
void beilcaStarbucks::draw(){
	double x = this->data->x * stretchX + offsetX;
	double y = (1-this->data->y) * stretchY + offsetY;
	gl::color(color);
	gl::drawSolidCircle(Vec2f(x,y), 4.0);
}