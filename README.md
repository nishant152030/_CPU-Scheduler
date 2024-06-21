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
![Screenshot 2024-06-20 014020](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/8af3ac90-8a74-4f52-9794-58a211bf3a11)

Figure 1. Intialising the App
- Request is processsed and results of the scheduling are sent back.
![Screenshot 2024-06-20 014042](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/09ea0799-1b81-485a-9cbe-8e028a3c12e9)

Figure 2. Return the response back to frontend
- App is running at port 8080. Output is also shown in terminal.
  ![Screenshot 2024-06-20 012236](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/1b89fbed-14ce-4ba1-84de-0b1a3176a7db)

### Frontend
- I implemented frontend simply using HTML,CSS and JavaScript. This include index.html, styles.css and script.js.
- Script.js renders the webpage dynamically. It sends process details to backend through POST request.
![Screenshot 2024-06-20 012016](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/a3c1c534-7380-43a8-89ba-c9f0017ce952)

  Figure 3. Sending post request to server
  ![Screenshot 2024-06-20 012101](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/17b1a21a-5870-4d3d-84e7-61e5ab44d631)
  Figure 4. Preview of frontend
![Screenshot 2024-06-20 012158](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/f22439cf-1072-418f-bf75-2aafa78fc914)
  Figure 5. Selecting algorithm, and filling details of processes
  ![Screenshot 2024-06-20 012210](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/3cd581ef-8df1-481e-9d77-db591cf58fd1)
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

![Screenshot 2024-06-20 042207](https://github.com/nishant152030/_CPU-Scheduler/assets/127687512/742e0050-62c7-4687-9379-bc229f875ebf)

## Dependencies
- C++ - Used as backend language
- Crow - Used as C++ framework
- Docker - To run the application
- CMake - To generate native build tool files
  
