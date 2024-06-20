function addProcessFields() {
  const numProcesses = document.getElementById('num-processes').value;
  const container = document.getElementById('processes-container');
  container.innerHTML = '';

  for (let i = 0; i < numProcesses; i++) {
    container.innerHTML += ` 
      <fieldset>
        <legend>Process ${i + 1}</legend>
        <label for="arrival-time-${i} style="margin-left:5px;">Arrival Time:</label>
        <input type="number" id="arrival-time-${i}" style="width:50px;margin-left:5px;" name="arrival-time-${i}" required>
        <label for="burst-time-${i}" style="margin-left:5px">Burst Time:</label>
        <input type="number" id="burst-time-${i}" style="width:50px;margin-left:5px;" name="burst-time-${i}" required>
        <label for="priority-${i}" style="margin-left:5px">Priority:</label>
        <input type="number" id="priority-${i}" style="width:50px;margin-left:5px;" name="priority-${i}" required>
      </fieldset>
    `;
  }
}

function showTimeQuantumInput() {
  var selector = document.getElementById("algorithmSelector");
  var timeQuantumDiv = document.getElementById("timeQuantumInput");

  if (selector.value === "RR") {
      timeQuantumDiv.classList.remove("hidden");
  } else {
      timeQuantumDiv.classList.add("hidden");
  }
}

function displayProcessDetails(response) {
  const tableBody = document.getElementById('processTable').getElementsByTagName('tbody')[0];
  tableBody.innerHTML='';
  // Insert process rows
  response.processes.forEach(process => {
      const row = tableBody.insertRow();
      row.insertCell(0).textContent = process.pid;
      row.insertCell(1).textContent = process.arrival_time;
      row.insertCell(2).textContent = process.burst_time;
      row.insertCell(3).textContent = process.waiting_time;
      row.insertCell(4).textContent = process.turnaround_time;
      row.insertCell(5).textContent = process.completion_time;
      row.insertCell(6).textContent = process.priority;
      row.insertCell(7).textContent = process.response_time;
  });

  // Display averages
  document.getElementById('avgWaitingTime').textContent = response.avg_waiting_time;
  document.getElementById('avgTurnaroundTime').textContent = response.avg_turnaround_time;
}

document.getElementById('process-form').addEventListener('submit', async function(event) {
  event.preventDefault();
  
  const algorithm = document.getElementById('algorithmSelector').value;
  const numProcesses = document.getElementById('num-processes').value;
  const processes = [];
  var timeQuantum;
  if(algorithm=="RR"){
    timeQuantum = document.getElementById('timeQuantum').value;
  }

  for (let i = 0; i < numProcesses; i++) {
    processes.push({
      pid: i + 1,
      arrival_time: document.getElementById(`arrival-time-${i}`).value,
      burst_time: document.getElementById(`burst-time-${i}`).value,
      priority: document.getElementById(`priority-${i}`).value
    });
  }

  // console.log(processes);
  // console.log(algorithm);
  // console.log(timeQuantum);

  const payload = {
    algorithm: algorithm,
    timeQuantum: timeQuantum,
    processes: processes
  };
  console.log(payload);
  try {
    const response = await fetch('http://localhost:8080/api/schedule', {
      method: 'POST',
      // mode: 'no-cors',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify( payload )
    });
    // console.log(response);
    const result = await response.json();
    console.log(result);
    displayProcessDetails(result);
  }catch (error) {
    console.log('Error:', error);
  }
  
});
