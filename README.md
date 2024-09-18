<p align=center>
<font size=26>OP2 Robotis Program Analysis</font>
</p>
<div align = center>
<img src="https://github.com/user-attachments/assets/4b712bbc-2507-44ba-8df7-70d613e6f5f8" length= "350px" width="350px">
</div>

1. Introduction:
   
   This document provides an analysis of the OP2 Robotis robot's program code. The program controls two primary actions: barbell tracking and simulated weightlifting. Below is a breakdown of key components of the program.

2. Rules of the competition:
<div align=center>
<img src="https://github.com/user-attachments/assets/ffd9a109-cf4f-4db0-920f-df0cef3b0ecb" length= "350px" width="350px">
</div>
   (1) Start from the Start Line and proceed to the Pick-up Line to find and pick up the barbell.

   (2) After picking up the barbell, walk to the Lift Line, lift the barbell to head height, and proceed to the Finish Line to complete.

3. Libraries and File Imports:
   
   The code begins by including necessary libraries, such as standard C++ libraries like <iostream> and <time.h>, as well as Robotis-provided libraries like LinuxDARwIn.h, Walking.h, Camera.h, and others. These libraries enable the management of robot movement, camera control, and data handling.

4. Global Definitions:
   
   Several global parameters are defined using #define statements. Some examples include:

      - MOTION_FILE_PATH: Defines the path for the motion files used by the robot.

      - STEP_TIME and STEP_TIME_2: Control the time intervals for walking behavior and movement amplitude.

5. Major Functions：
   
   The program consists of two major functional areas:
   
      (1) Tracking: The robot uses the camera to capture frames and track the position of a barbell using the ColorFinder object.
                    The Tracker and Follower classes coordinate to adjust the robot's head and body movements based on the barbell's position.
   
      (2) Simulated Weightlifting: The program uses three walking control modules (Walking, Walking2, Walking3) to simulate weightlifting. The predefined motions are executed using Action::GetInstance()->Start(), such as opening hands (Action::Start(15)) and squatting to lift (Action::Start(93)).

6. Program Flow：

   In the main function, the program initializes the robot's camera, walking modules, and motion manager. The robot operates in two modes: barbell tracking and weightlifting. Depending on the current mode and status, the robot switches between these actions.
   

Barbell Tracking & Following with Walking Video

 [![Demo GIF](https://github.com/user-attachments/assets/d44c1cb1-d2ae-44fa-b492-dcb49428449e)](https://github.com/user-attachments/assets/0d44f172-64af-4477-aa21-42dfd20e0d54)

<p align=center>
Walking2 Action Pose
</p>
<div align=center>
<img src="https://github.com/user-attachments/assets/9f6d708a-c9f7-44c0-acc0-43a8aba9562e" length= "900px" width="900px">
</div>
<p align=center>
Walking3 Action Pose
</p>
<div align=center>
<img src="https://github.com/user-attachments/assets/38860087-be11-4ad8-af7f-ebdfc6cde83f" length= "900px" width="900px">
</div>

<div align=center>
<img src="https://github.com/user-attachments/assets/92a5c83b-0543-4de7-839d-5f3ba02187f8" length= "900px" width="900px">
</div>





