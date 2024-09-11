/*
 * ColorFinder.h
 *
 *  Created on: 2011. 1. 10.
 *      Author: zerom
 */

#ifndef COLORFINDER_H_
#define COLORFINDER_H_

#include <string>

#include "Point.h"
#include "Image.h"
#include "minIni.h"

#define COLOR_SECTION   "Find Color"
#define INVALID_VALUE   -1024.0

namespace Robot
{
    class ColorFinder
    {
    private:
        Point2D m_center_point; 
        //儲存了檢測到的顏色區域的中心點，
        //Point2D 是一個自定義結構或類別，應該用來表示二維平面上的座標。

        void Filtering(Image* img);
	void RGBFiltering(Image* img);

    public:
        int m_hue;             /* 0 ~ 360  顏色的色相*/
        int m_hue_tolerance;   /* 0 ~ 180  色相的容差*/
        int m_min_saturation;  /* 0 ~ 100  飽和度*/
        int m_min_value;       /* 0 ~ 100  顏色的明暗程度 */
        double m_min_percent;  /* 0.0 ~ 100.0 */ //檢測到的顏色占圖像的百分比範圍
        double m_max_percent;  /* 0.0 ~ 100.0 */

        std::string color_section;

        Image*  m_result;

        ColorFinder();
	//初始化物件，設置初始的顏色範圍與參數。
        ColorFinder(int hue, int hue_tol, int min_sat, int min_val, double min_per, double max_per);
        virtual ~ColorFinder();
	//解構函式釋放資源。

        void LoadINISettings(minIni* ini);
        void LoadINISettings(minIni* ini, const std::string &section);
        void SaveINISettings(minIni* ini);
        void SaveINISettings(minIni* ini, const std::string &section);

        Point2D& GetPosition(Image* hsv_img);
	//接受一個處理過的HSV影像作為參數，並返回顏色檢測到的區域的中心座標
	Point2D& RGBGetPosition(Image* img);
    };
}

#endif /* COLORFINDER_H_ */
