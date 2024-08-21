/*
 *   BallTracker.cpp
 *
 *   Author: ROBOTIS
 *
 */

#include <math.h>
#include "Head.h"
#include "Camera.h"
#include "ImgProcess.h"
#include "BallTracker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace Robot;



BallTracker::BallTracker() :
        ball_position(Point2D(-1.0, -1.0))
{
	NoBallCount = 0;
	direction = 0;
}

BallTracker::~BallTracker()
{
}
 
void BallTracker::Process(Point2D pos)
{
	if(pos.X < 0 || pos.Y < 0)
	{
		ball_position.X = -1;
		ball_position.Y = -1;
		if(NoBallCount < NoBallMaxCount)
		{
			//Head::GetInstance()->MoveTracking();
			Head::GetInstance()->MoveByAngle(0, -7);
			NoBallCount++;
		}
		/*else
			Head::GetInstance()->InitTracking();*/
	}
	else
	{
		NoBallCount = 0;
		Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
		Point2D offset = pos - center;
		offset *= -1; // Inverse X-axis, Y-axis
		offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
		offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
		ball_position = offset;
		Head::GetInstance()->MoveTracking(ball_position);
		
	}
}


bool BallTracker::Process2(Point2D pos)
{
	if(pos.X < 0 || pos.Y < 0)
	{
		ball_position.X = -1;
		ball_position.Y = -1;
		/*if(NoBallCount < NoBallMaxCount)
		{
			Head::GetInstance()->MoveTracking();
			NoBallCount++;
		}
		else
		{*/
			Head::GetInstance()->InitTracking();
			if(direction2%4== 0)
			{
				Head::GetInstance()->MoveByAngle(-10, 40); //-40
				sleep(1);		
			}			
			else if(direction2%4 ==1 || direction2%4== 3)
			{
				Head::GetInstance()->MoveByAngle(0, 40);
				sleep(1);
			}			
			else if(direction2%4 ==2)
			{
				Head::GetInstance()->MoveByAngle(10, 40);  //40
				sleep(1);	
			}
			direction2 += 1;
			printf("Direction2 = %d\n", direction2);
			
		//}
		return false;
	}
	else
	{
		NoBallCount = 0;
		Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
		Point2D offset = pos - center;
		offset *= -1; // Inverse X-axis, Y-axis
		offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
		offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle

		ball_position = offset;
		Head::GetInstance()->MoveTracking(ball_position);
		return true;
	}
}

bool BallTracker::Process3(Point2D pos)
{
	if(pos.X < 0 || pos.Y < 0)
	{
		ball_position.X = -1;
		ball_position.Y = -1;
		/*if(NoBallCount < NoBallMaxCount)
		{
			Head::GetInstance()->MoveTracking();
			NoBallCount++;
		}*/
		//else
		//{
			Head::GetInstance()->InitTracking();
			if(direction%4== 0)
			{
				Head::GetInstance()->MoveByAngle(-60, 30);
				sleep(1);		
			}			
			else if(direction%4 ==1 || direction%4== 3)
			{
				Head::GetInstance()->MoveByAngle(0, 30);
				sleep(1);
			}			
			else if(direction%4 ==2)
			{
				Head::GetInstance()->MoveByAngle(60, 30);
				sleep(1);	
			}
			direction += 1;
			printf("direction = %d\n", direction);
			
		//}
		return false;
	}
	else
	{
		NoBallCount = 0;
		Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
		Point2D offset = pos - center;
		offset *= -1; // Inverse X-axis, Y-axis
		offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
		offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle

		ball_position = offset;
		Head::GetInstance()->MoveTracking(ball_position);
		return true;
	}
}
void BallTracker::Basket_Aiming(Point2D pos,bool hand)
{
	if(pos.X < 0 || pos.Y < 0)
	{
		ball_position.X = -1;
		ball_position.Y = -1;
		if(NoBallCount < NoBallMaxCount)
		{
			Head::GetInstance()->MoveTracking();
			
			NoBallCount++;
		}
		else
		{
			Head::GetInstance()->InitTracking();
			
		}
	}
	else
	{
		if(hand)
		{
			NoBallCount = 0;
			Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
			Point2D offset;
			offset.X = pos.X - center.X - 40;
			offset.Y = pos.Y - center.Y;

			offset *= -1; // Inverse X-axis, Y-axis
			offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
			offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
			ball_position = offset;
			Head::GetInstance()->MoveTracking(ball_position);
		}
		if(!hand)
		{
			NoBallCount = 0;
			Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
			Point2D offset;
			offset.X = pos.X - center.X + 55;
			offset.Y = pos.Y - center.Y;

			offset *= -1; // Inverse X-axis, Y-axis
			offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
			offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
			ball_position = offset;
			Head::GetInstance()->MoveTracking(ball_position);
		}
	}
}

void BallTracker::Ball_Aiming(Point2D pos)
{
	if(pos.X < 0 || pos.Y < 0)
	{
		ball_position.X = -1;
		ball_position.Y = -1;
		if(NoBallCount < NoBallMaxCount)
		{
			Head::GetInstance()->MoveTracking();
			NoBallCount++;
		}
		else
			Head::GetInstance()->InitTracking();
	}
	else
	{
		NoBallCount = 0;
		Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
		Point2D offset;
		offset.X = pos.X - center.X;
		offset.Y = pos.Y - center.Y;

		offset *= -1; // Inverse X-axis, Y-axis
		offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
		offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
		ball_position = offset;
		Head::GetInstance()->MoveTracking(ball_position);
	}

}



