#include <iostream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>
#include <signal.h>
#include "mjpg_streamer.h"
#include "LinuxDARwIn.h"
#include "MotionStatus.h"
#include "Camera.h"
#include "JointData.h"
#include "StatusCheck.h"
#include "VisionMode.h"
#include "Walking.h"
#include "Walking2.h"
#include "Walking3.h"

using namespace Robot;
using namespace std;

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../../Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../../Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "../../../Data/config.ini"
#define INI_FILE_PATH2      "../../../Data/config.ini2"
#define INI_FILE_PATH3      "../../../Data/config.ini3"
#define SCRIPT_FILE_PATH    "script.asc"

#define U2D_DEV_NAME0        "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

// Parameters for walking behavior
#define STEP_TIME 10   
#define STEP_TIME_2 30

#define turnX 9
#define turnY 0
#define turnA 0

#define turnXX 7
#define turnYY 0
#define turnAA 0.5


void change_current_dir()
{
    char exepath[1024] = {0};
    if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        chdir(dirname(exepath));
}

void sighandler(int sig)
{
    exit(0);
}


int main(void)
{
	int part = 1;

	//////////BALL FOLLOWING///////////
	int n = 0;
	int param[JointData::NUMBER_OF_JOINTS * 5];
	int wGoalPosition, wStartPosition, wDistance;
	double tilt;

	/////////WEIGHTLIFTING////////////
	int counter_1 = 0;
    	int counter_2 = 0;
    	int test = 0;
	int firm_ver = 0;
	
	//////////////////////////////Ball Following Initialize Start///////////////////////////////////
	change_current_dir();

	Image* rgb_ball = new Image(Camera::WIDTH, Camera::HEIGHT, Image::RGB_PIXEL_SIZE);

	minIni* ini = new minIni(INI_FILE_PATH);
	minIni* ini_2 = new minIni(INI_FILE_PATH2);
    	minIni* ini_3 = new minIni(INI_FILE_PATH3);


	LinuxCamera::GetInstance()->Initialize(0);
	LinuxCamera::GetInstance()->LoadINISettings(ini);

	mjpg_streamer* streamer = new mjpg_streamer(Camera::WIDTH, Camera::HEIGHT);

	ColorFinder* ball_finder = new ColorFinder();
	ball_finder->LoadINISettings(ini);
	httpd::ball_finder = ball_finder;

	BallTracker tracker = BallTracker();
	BallFollower follower = BallFollower();
	follower.DEBUG_PRINT = true;

	LinuxCM730 linux_cm730(U2D_DEV_NAME0);
	CM730 cm730(&linux_cm730);
	if(MotionManager::GetInstance()->Initialize(&cm730) == false)
	{
		printf("Fail to initialize Motion Manager!\n");
			return 0;
	}
	MotionManager::GetInstance()->LoadINISettings(ini);
	MotionManager::GetInstance()->LoadINISettings(ini_2);
    	MotionManager::GetInstance()->LoadINISettings(ini_3);
	Walking::GetInstance()->LoadINISettings(ini);

	MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
	motion_timer->Start();

	for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
	{
		wStartPosition = MotionStatus::m_CurrentJoints.GetValue(id);
		wGoalPosition = Walking::GetInstance()->m_Joint.GetValue(id);
		if( wStartPosition > wGoalPosition )
			wDistance = wStartPosition - wGoalPosition;
		else
			wDistance = wGoalPosition - wStartPosition;

		wDistance >>= 2;
		if( wDistance < 8 )
			wDistance = 8;

		param[n++] = id;
		param[n++] = CM730::GetLowByte(wGoalPosition);
		param[n++] = CM730::GetHighByte(wGoalPosition);
		param[n++] = CM730::GetLowByte(wDistance);
		param[n++] = CM730::GetHighByte(wDistance);
	}
	//////////////////////////////Ball Following Initialize End////////////////////////////////////

	//////////////////////////////WeightLifting Initialize Start///////////////////////////////////		

	//MotionManager::GetInstance()->LoadINISettings(ini);
	Walking2::GetInstance()->LoadINISettings(ini_2); 
	Walking3::GetInstance()->LoadINISettings(ini_3);

	MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Walking2::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Walking3::GetInstance());

	if(cm730.ReadByte(JointData::ID_HEAD_PAN, MX28::P_VERSION, &firm_ver, 0)  != CM730::SUCCESS)
	{
		fprintf(stderr, "Can't read firmware version from Dynamixel ID %d!! \n\n", JointData::ID_HEAD_PAN);
		exit(0);
	}

	if(0 < firm_ver && firm_ver < 27)
	{
		#ifdef MX28_1024
		Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
		#else
		fprintf(stderr, "MX-28's firmware is not support 4096 resolution!! \n");
		fprintf(stderr, "Upgrade MX-28's firmware to version 27(0x1B) or higher.\n\n");
		exit(0);
		#endif
	}
	else if(27 <= firm_ver)
	{
		#ifdef MX28_1024
		fprintf(stderr, "MX-28's firmware is not support 1024 resolution!! \n");
		fprintf(stderr, "Remove '#define MX28_1024' from 'MX28.h' file and rebuild.\n\n");
		exit(0);
		#else
		Action::GetInstance()->LoadFile((char*)MOTION_FILE_PATH);
		#endif
	}
	else
		exit(0);

	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	MotionManager::GetInstance()->SetEnable(true);
	
	cm730.WriteByte(CM730::P_LED_PANNEL, 0x01|0x02|0x04, NULL);

	LinuxActionScript::PlayMP3("../../../Data/mp3/Demonstration ready mode.mp3");

	Action::GetInstance()->Start(16);
	while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	
	///////////////////////WeightLifting Initialize End//////////////////////////////////////////////

    while(1)
    {
    	StatusCheck::Check(cm730);

        if(StatusCheck::m_is_started == 0)
            continue;

        switch(StatusCheck::m_cur_mode)
        {
            case READY:
                break;
            case SOCCER:
	        switch(part)
	        {
	            case 1:

					printf( "\n===== Ball following  for DARwIn OP2 =====\n\n");
					Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
					Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
					MotionManager::GetInstance()->SetEnable(true);

	            	while(tilt >= -24.9)
		           	{   
		                Point2D pos;
		                LinuxCamera::GetInstance()->CaptureFrame();
						tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
		                memcpy(rgb_ball->m_ImageData, LinuxCamera::GetInstance()->fbuffer->m_RGBFrame->m_ImageData, LinuxCamera::GetInstance()->fbuffer->m_RGBFrame->m_ImageSize);

		                tracker.Process(ball_finder->GetPosition(LinuxCamera::GetInstance()->fbuffer->m_HSVFrame));
		                follower.Process(tracker.ball_position);

		                cout << "Head tilt = " << tilt << endl;
		                for(int i = 0; i < rgb_ball->m_NumberOfPixels; i++)
		                {
		                    if(ball_finder->m_result->m_ImageData[i] == 1)
		                    {
		                        rgb_ball->m_ImageData[i*rgb_ball->m_PixelSize + 0] = 255;
		                        rgb_ball->m_ImageData[i*rgb_ball->m_PixelSize + 1] = 0;
		                        rgb_ball->m_ImageData[i*rgb_ball->m_PixelSize + 2] = 0;
		                    }
		                }
		                        streamer->send_image(rgb_ball);
		            }

					cout << "-1" << endl;
					Walking::GetInstance() -> Stop();
					sleep(1);
					Action::GetInstance()->m_Joint.SetEnableBody(true, true);
					MotionManager::GetInstance()->SetEnable(true);
					Action::GetInstance()->Start(16);
					while(Action::GetInstance()->IsRunning()) usleep(8*1000);
					part = 2;

	            break;

	            case 2:
	                if(test == 0)
	                {
	                    if(Action::GetInstance()->IsRunning() == 0)
	                    {
	                        Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
	                        Head::GetInstance()->MoveByAngle(0, 2);
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	                       	Action::GetInstance()->Start(15);//open hand
	                       	while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        sleep(1);
	                        Action::GetInstance()->Start(93);//squal down and catch
	                        //while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        
	                        //Action::GetInstance()->m_Joint.SetAngle(22, 15);//left close
	                        //Action::GetInstance()->m_Joint.SetAngle(21,-15);//right close
	      					while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	      					sleep(1);
	                        Action::GetInstance()->Start(96);
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        sleep(1);
	                        test=1;
	                        printf("test=%d",test);
	                    }
	                }//end--test = 0;

	                if(test == 1)    //first step
	                {
	                    if(Action::GetInstance()->IsRunning() == 0 && counter_1 <= 2 )
	                    {
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        //Walking2::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	                        Walking2::GetInstance()->m_Joint.SetEnableLowerBody(true, true);
	                        Walking2::GetInstance()->X_MOVE_AMPLITUDE=5;
	                        Walking2::GetInstance()->A_MOVE_AMPLITUDE=0;
	                        Walking2::GetInstance()->Y_MOVE_AMPLITUDE=-3;

	                        Walking2::GetInstance()->HIP_PITCH_OFFSET=-18;//-18 -10
	                        Walking2::GetInstance()->PELVIS_OFFSET=1;

	                        Walking2::GetInstance()-> Start();
	                        counter_1++;
	                        printf("counter_1 = %d\n\n",counter_1);
	                        sleep(1);
	                    }

	                    else if( counter_1 <= STEP_TIME)
	                    {
	                        
	                        Walking2::GetInstance()->X_MOVE_AMPLITUDE=turnX + 4;//turnX=9
	                        Walking2::GetInstance()->A_MOVE_AMPLITUDE=turnA;//turnA=0
	                        Walking2::GetInstance()->Y_MOVE_AMPLITUDE=turnY + 3;//turnY=0
	                        Walking2::GetInstance()->HIP_PITCH_OFFSET=-18;//-18  -10
	                        Walking2::GetInstance()->PELVIS_OFFSET=1;
	                        Walking2::GetInstance()-> Start();
	                        counter_1++;
	                        printf("counter_1 = %d\n\n",counter_1);
	                        sleep(1);
	                    }

	                    if(counter_1 > STEP_TIME)
	                    {
	                        if(Action::GetInstance()->IsRunning() == 0)
	                        {
	                            Walking2::GetInstance()->Initialize();
	                            test = 2;
	                            counter_1 = 0;
	                            sleep(1);
	                        }
	                    }
	                }//end--test = 1
	                
	                if(test == 2)
	                {
	                    if(Action::GetInstance()->IsRunning() == 0)
	                    {
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        
	                        Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	                        Action::GetInstance()->Start(101);
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        Action::GetInstance()->Start(102);
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        Action::GetInstance()->Start(111);
	                        while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        
	                        test = 3;
	                        sleep(1);
	                    }
	                }//end--test = 2
	            
	                if(test == 3)
	                {
	                    if(Action::GetInstance()->IsRunning() == 0 && counter_2 <= 1)
	                    {
	    	                while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	                        //Walking3::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
	                        Walking3::GetInstance()->m_Joint.SetEnableLowerBody(true, true);
				Walking3::GetInstance()->A_MOVE_AMPLITUDE =  0;//2
	                        Walking3::GetInstance()->X_MOVE_AMPLITUDE = 15;//15
	                        Walking3::GetInstance()->Y_MOVE_AMPLITUDE = 0;//-2
	                        //Walking3::GetInstance()->Z_MOVE_AMPLITUDE = 20;
	                        Walking3::GetInstance()-> Start();
	                        counter_2++;
	                        printf("counter_2 = %d\n\n",counter_2);
	                        sleep(1);
	                    }
	                    else if(counter_2 > 1 && counter_2 <= STEP_TIME_2)
	                    {
	                        Walking3::GetInstance()->A_MOVE_AMPLITUDE = 2 ;//1
	                        Walking3::GetInstance()->X_MOVE_AMPLITUDE = 15;//15
	                        Walking3::GetInstance()->Y_MOVE_AMPLITUDE = 0;//0
	                        //Walking::GetInstance()->Z_MOVE_AMPLITUDE = 20;
	                        //Walking::GetInstance()->HIP_PITCH_OFFSET= -2;

	                        Walking3::GetInstance()-> Start();
	                        counter_2++;
	                        printf("counter_2 = %d\n\n",counter_2);
	                        sleep(1);
	                    }
	                    if(counter_2 > STEP_TIME_2)
	                    {
	                        if(Action::GetInstance()->IsRunning() == 0)
	                        {
	                            Walking3::GetInstance()->Stop();
	                            test = 4;
	                            counter_2 = 0;
	                            sleep(1);
	                        }
	                    }//end--test = 3;
	                }

	            break;

	        }//switch_ballfollow&weightlifting            
    	}//switch(mode control)
    }

	return 0;
}
