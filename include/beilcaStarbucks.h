/*	Author:	Carter Beil
	Date:	October 20, 2012
	File: beilcaStarbucks.h
*/

#pragma once
#include "cinder/Rand.h"
#include <math.h>
#include "Starbucks.h"
#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"



/*
 class Node{
public:		

	Node* left_;
	Node* right_;
	Entry* data;

	Node();
	Node(Entry e);		

  };
  */

 class beilcaStarbucks : public Starbucks {
 public:

	 //Create a null pointer
	beilcaStarbucks();
	beilcaStarbucks(Entry* data);
	~beilcaStarbucks();
	double stretchX;
	double stretchY;
	double offsetX;
	double offsetY;
	ci::Color8u color;

	 //beilcaStarbucks::beilcaStarbucks(Entry* e);

	 int arrayLength;
	 Entry* nearestStarbucks;
	 Entry* currentStarbucks;
	 Entry* data;

	 //Supposed to check and make sure we aren't putting values that are too close to one another in the array...

	 //But since my K-D tree has failed, I'm not sure how I can implement this on a regular array, but I shall try!
	 static const int sameLocation = 0.00001;
	 
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
	 virtual void build(Entry* e, int n);

	 void randomize(Entry* e, int arrayLength);

	 //To delete a Starbucks if it is the same location as another Starbucks
	 void deleteNode(Entry* e);


	 //I will use the insert function in order to build my K-D tree
	 //Node* insert(Entry* e, Node* r, bool xLevel);

	 //This function will most likely be implemented exactly as it was stated in class
	 //..at least to the best of my knowledge

	 /*
	 * Return a pointer to the entry that is closest to the given coordinates. Your
	 *  answer may be approximate, but then you will lose points on the "Accuracy" quality measure
	 */
	 virtual Entry* getNearest(double x, double y);

	 double search(Entry e, double x, double y);

	 void draw();

 };