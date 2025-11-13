import './App.css';
import React, { useState, useEffect } from "react"
import axios from "axios"

/**
 *  Please read README.md for instructions on how to run this program.
 */

function App() {
  //=============================================================================
  // Login
  //=============================================================================
  const [username, setUsername] = useState("")
  const [password, setPassword] = useState("")
  const [authToken, setAuthToken] = useState("")
  const [userid, setUserid] = useState()

  const handleUsername = (e) => {
    setUsername(e.target.value)
  }

  const handlePassword = (e) => {
    setPassword(e.target.value)
  }

  const handleLogin = () => {
    // Send a POST request
    axios({
      method: 'post',
      url: 'https://api.taiga.io/api/v1/auth',
      data: {
        "password": password,
        "type": "normal",
        "username": username
      }
    })
    .then(function(response){
      console.log("00000 ", response.data)
      setUserid(response.data.id)
      setAuthToken(response.data.auth_token)
    })
    .catch(function(error){
      console.log(error)
    })
  }

  //=============================================================================
  // List of projects
  // User choose a project
  //=============================================================================
  const [projects, setProjects] = useState([])
  const [selectedProject, setSelectedProject] = useState()
  
  useEffect(() => {
    setProjects([])

    axios({
      method: 'get',
      url: `https://api.taiga.io/api/v1/projects?member=${userid}`,
      headers: {
        Authorization: `Bearer ${authToken}`
      }
    })
    .then(function(response){
      console.log("0.2", response.data)
      setProjects(response.data)
    })
    .catch(function(error){
      console.log(error)
    })

  }, [authToken])

  //=============================================================================
  // Project members and roles
  // List of sprints
  //=============================================================================
  const [members, setMembers] = useState([])
  const [milestones, setMilestones] = useState([])

  useEffect(() => {
    setMembers([])
    setMilestones([])

    axios({
      method: 'get',
      url: `https://api.taiga.io/api/v1/projects/${selectedProject}`,
      headers: {
        Authorization: `Bearer ${authToken}`
      }
    })
    .then(function(response){
      console.log(response.data)
      setMembers(response.data.members)
      setMilestones(response.data.milestones)
      console.log("11111 ", members)
      console.log("22222 ", milestones)
    })
    .catch(function(error){
      console.log(error)
    })

  }, [selectedProject])

  //=============================================================================
  // List of sprints
  //=============================================================================
  const [sprints, setSprints] = useState([])

  useEffect(() => {
    setSprints([])

    milestones.map(m => {
      axios({
        method: 'get',
        url: `https://api.taiga.io/api/v1/milestones/${m["id"]}`,
        headers: {
          Authorization: `Bearer ${authToken}`
        }
      })
      .then(function(response){
        setSprints(oldArr => [...oldArr, response.data])
        console.log("33333 ", response.data)
      })
      .catch(function(error){
        console.log(error)
      })
    })

  }, [milestones])
  
  //=============================================================================
  // User choose a sprint
  // List of user stories
  //=============================================================================
  const [selectedSprint, setSelectedSprint] = useState()
  const [userStories, setUserStories] = useState([])

  useEffect(() => {
    setUserStories([])

    sprints.map(s => {
      console.log("4.2", s["id"], selectedSprint)
      if (s["id"] == selectedSprint) {
        console.log("4.4", s["id"], selectedSprint)
        s["user_stories"].map(us => {
          setUserStories(oldArr => [...oldArr, us])
          console.log("4.6", us)
        })
      }
    })

  }, [selectedSprint])

  //=============================================================================
  // List of tasks
  //=============================================================================
  const [tasks, setTasks] = useState([])

  useEffect(() => {
    setTasks([])

    axios({
      method: 'get',
      url: `https://api.taiga.io/api/v1/tasks?milestone=${selectedSprint}`,
      headers: {
        Authorization: `Bearer ${authToken}`
      }
    })
    .then(function(response){
      console.log("55555 ", response.data)
      setTasks(response.data)

    })
    .catch(function(error){
      console.log(error)
    })

  }, [selectedSprint])

  //=============================================================================
  // Number of tasks for each team member
  //=============================================================================
  const [numTasksEachMem, setNumTasksEachMem] = useState([])

  useEffect(() => {
    setNumTasksEachMem([])

    members.map(m => {
      var count = 0
      tasks.map(t => {
        if (t["assigned_to"] === m["id"]) {
          count++
        }
      })
      setNumTasksEachMem(oldArr => [...oldArr, m["full_name"] + ": " + count])
    })

  }, [tasks])


  return (
    <div className="App">
      <label>
        <br/>Username:
        <input type="text" name="username" onChange={handleUsername} />
      </label>
      <label>
        Password:
        <input type="text" name="password" onChange={handlePassword} />
      </label>
      <button onClick={handleLogin}>Log In</button>

      <h2>Auth Token</h2>
      {authToken}
      <h2>Select From a List of Projects</h2>
      {projects && projects.map(p => { return <button id={p["id"]} type="button" onClick={e => setSelectedProject(e.target.id)}>{p["name"]} - {p["id"]}</button>})}
      <h2>Memebers and Roles</h2>
      {members && members.map(m => { return <pre>{m["full_name"]} - {m["role_name"]}</pre>})}
      <h2>List of Sprints</h2>
      {sprints && sprints.map(s => { return <pre>{s["name"]} - Start: {s["estimated_start"]} - End: {s["estimated_finish"]} - Total Pts: {s["total_points"]} - Finished Pts: {s["closed_points"]}</pre>})}
      <h2>Select a Sprint</h2>
      {sprints && sprints.map(s => { return <button id={s["id"]} type="button" onClick={e => setSelectedSprint(e.target.id)}>{s["name"]} - {s["id"]}</button>})}
      <h2>User Stories of Selected Sprint</h2>
      {userStories && userStories.map(us => { return <pre><br/>{us["subject"]}<br/> - Finished: {us["is_closed"].toString()} - Created Date: {us["created_date"]} - Moved Date: {us["modified_date"]}</pre> })}
      <h2>Tasks of Selected Sprint</h2>
      {tasks && tasks.map(t => { return <pre><br/>Task Name: {t["subject"]}<br/> Task Id: {t["ref"]} - Assignee: {t["assigned_to_extra_info"]["full_name_display"]} </pre> })}
      <h2>Number of Tasks for Each Team Member</h2>
      {numTasksEachMem && numTasksEachMem.map(n => { return <pre>{n}</pre> })}
    </div>
  );
}

export default App;
