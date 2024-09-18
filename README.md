<p align=center>
   <font size = 300>Research and Development of Bipedal Intelligent Robot </font>
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
   
<p align="center">
Barbell Tracking & Following with Walking Video
</p>
<p align="center">
    <a href="https://youtube.com/shorts/cfD9wAqq4AE?feature=share">
        <img src="https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExaXNidGNnYTF4NWMxbjh5Mmw2c2ZlcTFrdjI0aHR4MGUwOWw1aWxjbiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/8927bavbhroiW5fhwQ/giphy.gif" length= "250px" width="250px"/>
    </a>
</p>


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





