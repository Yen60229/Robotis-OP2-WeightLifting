/*
 *   Point.h
 *
 *   Author: ROBOTIS
 *
 */

#ifndef _POINT_H_
#define _POINT_H_


namespace Robot
{	
	class Point2D
	{
	private:

	protected:

	public:
		double X;
		double Y;

		Point2D();
		//Point2D主要用於表示影像中的點，如顏色檢測到的物體的中心點
		Point2D(double x, double y);
		//初始化X和Y座標的建構函式
		Point2D(const Point2D &point);		
		~Point2D();

		static double Distance(Point2D &pt1, Point2D &pt2);

		Point2D & operator = (Point2D &point);
		Point2D & operator += (Point2D &point);
		Point2D & operator -= (Point2D &point);
		Point2D & operator += (double value);
		Point2D & operator -= (double value);
		Point2D & operator *= (double value);
		Point2D & operator /= (double value);
		Point2D operator + (Point2D &point);
		Point2D operator - (Point2D &point);
		Point2D operator + (double value);
		Point2D operator - (double value);
		Point2D operator * (double value);
		Point2D operator / (double value);
	};

	class Point3D
	{
	private:

	protected:

	public:
		double X;
		double Y;
		double Z;
		
		Point3D();
		Point3D(double x, double y, double z);
		Point3D(const Point3D &point);
		~Point3D();

		static double Distance(Point3D &pt1, Point3D &pt2);
		//態函式，用於計算兩個點之間的距離

		Point3D & operator = (Point3D &point);
		Point3D & operator += (Point3D &point);
		Point3D & operator -= (Point3D &point);
		Point3D & operator += (double value);
		Point3D & operator -= (double value);
		Point3D & operator *= (double value);
		Point3D & operator /= (double value);
		Point3D operator + (Point3D &point);
		Point3D operator - (Point3D &point);
		Point3D operator + (double value);
		Point3D operator - (double value);
		Point3D operator * (double value);
		Point3D operator / (double value);
	};
}

#endif
