/*
 *   BallTracker.h
 *
 *   Author: ROBOTIS
 *
 */

#ifndef _BALL_TRACKER_H_
#define _BALL_TRACKER_H_

#include <string.h>

#include "Point.h"
#include "minIni.h"

namespace Robot
{
	class BallTracker
	{
	private:
		int NoBallCount;
		static const int NoBallMaxCount = 3;//15
		int direction, direction2;  //0:right  (1, 3):mid  2:left 

	public:
        	Point2D     ball_position;

		BallTracker();
		~BallTracker();
		
		
		void Process(Point2D pos);   //void
		bool Process2(Point2D pos);   //void
		bool Process3(Point2D pos);  
		void Basket_Aiming(Point2D pos,bool hand);
		void Ball_Aiming(Point2D pos);
	};
}

#endif
