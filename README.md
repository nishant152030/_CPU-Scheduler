# CPU Scheduler

## Introduction
CPU scheduler is an application which is used to simulate the scheduling algorithms used by CPU for scheduling processes.
CPU Scheduling is a process that allows one process to use the CPU while another process is delayed (in standby) due to unavailability of any resources such as I / O etc, thus making full use of the CPU. 
The purpose of CPU Scheduling is to make the system more efficient, faster, and fairer. <br>
<br>
This project is an implementation of the four scheduling algorithms. These are First-Come-First-Serve(FCFS), Shortest Remaining Time First(SRTF), Priority scheduling and Round Robin. It also supports auto scheduling
feature which selects optimal algorithm for scheduling processes.

## Implementation
### Backend
- The backend is written in C++. All the algorithms are implemented in main.py.
- For setting up the server, I have used Crow, which is a C++ framework for creating HTTP or Websocket web services. As this framework is new to me, therefore it takes a lot of time in reading its documentation.
- Using crow, first a POST route 'api/schedule' is created for receiving request from frontend.
![Screenshot 2024-06-20 014020](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/fcc10af8-c3f0-4a4a-9aed-eb9f4a69c39b)
Figure 1. Intialising the App
- Request is processsed and results of the scheduling are sent back.
![Screenshot 2024-06-20 014042](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/c358543a-ebf7-4f67-b998-56715f9f9a4c)
Figure 2. Return the response back to frontend
- App is running at port 8080. Output is also shown in terminal.
  ![Screenshot 2024-06-20 012236](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/2d32cdf2-ff36-43bb-aed0-a793c46c5175)
### Frontend
- I implemented frontend simply using HTML,CSS and JavaScript. This include index.html, styles.css and script.js.
- Script.js renders the webpage dynamically. It sends process details to backend through POST request.
  ![Screenshot 2024-06-20 034558](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/171fd0c3-95d0-4620-b88c-aad1b370d6d6)
  Figure 3. Sending post request to server
![Screenshot 2024-06-20 012101](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/c2d490b6-0bf4-47f4-a761-24f2b6651376)
  Figure 4. Preview of frontend
  ![Screenshot 2024-06-20 012158](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/5d0e867c-d987-4cad-9b3e-12208a6710e4)
  Figure 5. Selecting algorithm, and filling details of processes
![Screenshot 2024-06-20 012210](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/812a41e6-2f0a-47fc-907e-b4c7a087ade1)
  Figure 6. Results Obtained

## Running the Application
### Clone the repository
```
git clone https://github.com/nishant152030/CPU-Scheduler.git
```
### Run the Server
#### Method 1. Using Docker(Preferable)
- Run the following in the terminal after navigating to the directory.
  ```
  docker build -t my-cmake-app.
  docker run -p 8080:8080 my-cmake-app
  ```
#### Method 2. Using executable
- Open main.exe to start the server at 8080.
- This method may not work on your device because it is build in windows.
### Go to Application
- 1. Navigate to the templates directory and run the following commands to launch index.html.
     ```
     python -m http.server
     ```
     or
     ```
     npm install http-server -g
     http-server
     ```
- 2. Open index.html in any IDE (e.g. vscode) and launch open server. <br>
<br>
  NOTE: Currently, server is not allowing to fetch cross origin resources. I tried to add necessary headers but it didn't work. So, to get data from the server and correctly run the application, we need to add CORS extension to our browser and allow Allow-Control-Allow-Headers in the options page.<br>

![Screenshot 2024-06-20 042207](https://github.com/nishant152030/CPU-Scheduler/assets/127687512/812ef86c-63e5-4b3d-b1f0-300d2acad5ee)

## Dependencies
- C++ - Used as backend language
- Crow - Used as C++ framework
- Docker - To run the application
- CMake - To generate native build tool files
  
