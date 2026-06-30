import { useEffect, useState } from "react";
import axios from "axios";
import "./App.css";

import {
  FaRobot,
  FaTasks,
  FaChartLine,
  FaFire,
  FaCalendarAlt
} from "react-icons/fa";

const API_URL = "http://localhost:8080";

function App() {
  const [tasks, setTasks] = useState([]);
  const [analytics, setAnalytics] = useState({});
  const [priority, setPriority] = useState([]);
  const [dayPlan, setDayPlan] = useState(null);


  const [form, setForm] = useState({
    title: "",
    deadline: "",
    estimatedHours: "",
    category: "Study",
    importance: "Medium",
  });

  const fetchData = async () => {
    const tasksRes = await axios.get(`${API_URL}/tasks`);
    const analyticsRes = await axios.get(`${API_URL}/analytics`);
    const priorityRes = await axios.get(`${API_URL}/priority`);

    setTasks(tasksRes.data);
    setAnalytics(analyticsRes.data);
    setPriority(priorityRes.data);
  };

  useEffect(() => {
    fetchData();
  }, []);

  const addTask = async (e) => {
    e.preventDefault();

    await axios.post(`${API_URL}/tasks`, {
      ...form,
      estimatedHours: Number(form.estimatedHours),
    });

    setForm({
      title: "",
      deadline: "",
      estimatedHours: "",
      category: "Study",
      importance: "Medium",
    });

    fetchData();
  };

  const updateStatus = async (id, status) => {
    await axios.put(`${API_URL}/tasks/status`, {
      id,
      status,
    });

    fetchData();
  };

  const generateDay = async () => {
    const res = await axios.get(`${API_URL}/generate-day`);
    setDayPlan(res.data);
  };

  return (
    <div className="app">
      <div className="hero">
        <h1>🚀 Last-Minute Life Saver</h1>
        <p>Your AI Productivity Companion</p>
      </div>
    <h2 style={{ marginTop: "25px" }}>
      👋 Welcome back, Avisha!
    </h2>

<p className="subtitle">
  Let AI help you stay ahead of your deadlines.
</p>

      <section className="card">
        <h2>Add Task</h2>
        <form onSubmit={addTask} className="form">
          <input
            placeholder="Task name"
            value={form.title}
            onChange={(e) => setForm({ ...form, title: e.target.value })}
            required
          />

          <input
            type="date"
            value={form.deadline}
            onChange={(e) => setForm({ ...form, deadline: e.target.value })}
            required
          />

          <input
            type="number"
            placeholder="Estimated hours"
            value={form.estimatedHours}
            onChange={(e) =>
              setForm({ ...form, estimatedHours: e.target.value })
            }
            required
          />

          <select
            value={form.category}
            onChange={(e) => setForm({ ...form, category: e.target.value })}
          >
            <option>Study</option>
            <option>Work</option>
            <option>Personal</option>
            <option>Career</option>
          </select>

          <select
            value={form.importance}
            onChange={(e) => setForm({ ...form, importance: e.target.value })}
          >
            <option>High</option>
            <option>Medium</option>
            <option>Low</option>
          </select>

          <button type="submit">Add Task</button>
        </form>
      </section>

      <section className="stats">
        <div>Total: {analytics.totalTasks ?? 0}</div>
        <div>Completed: {analytics.completed ?? 0}</div>
        <div>Pending: {analytics.pending ?? 0}</div>
        <div>Skipped: {analytics.skipped ?? 0}</div>
        <div>Score: {analytics.productivityScore ?? 0}%</div>
      </section>

      <section className="card">
        <h2>Tasks</h2>
        {tasks.map((task) => (
          <div className="task" key={task.id}>
            <div>
              <h3>{task.title}</h3>
              <p>
                Due: {task.deadline} | {task.estimatedHours} hrs |{" "}
                {task.importance}
              </p>
              <p>Status: {task.status}</p>
            </div>

            <div className="actions">
              <button onClick={() => updateStatus(task.id, "In Progress")}>
                Start
              </button>
              <button onClick={() => updateStatus(task.id, "Completed")}>
                Complete
              </button>
              <button onClick={() => updateStatus(task.id, "Skipped")}>
                Skip
              </button>
            </div>
          </div>
        ))}
      </section>

      <section className="card">
        <h2>
            <FaRobot /> AI Productivity Coach
        </h2>
        {priority.map((item) => (
          <div className="priority" key={item.id}>
            <h3>{item.title}</h3>
            <p>🔥 Priority Score: {item.priorityScore}</p>
            <p>
              ⚠️ Risk:
              <span
                className={
                  item.risk=="High"
                    ? "risk-high"
                    : item.risk=="Medium"
                    ? "risk-medium"
                    : "risk-low"
                }
              >
                {" "}
                {item.risk}
              </span>
            </p>
            <p>📅 Days Remaining: {item.daysRemaining}</p>
            <p>
            <b>Recommendation</b>
            <br />
            {item.recommendation}
            </p>
            <button 
              className="ai-button"
              onClick={generateDay}
              >
               ✨ Generate My Day
            </button>
          </div>
        ))}
      </section>

      {dayPlan && (
        <section className="card">
          <h2>🤖 Today's AI Plan</h2>
          <p>{dayPlan.message}</p>
          {dayPlan.plan.map((item, index) => (
            <div key={index} className="priority">
              <h3>{item.task}</h3>
              <p>🕒 {item.time}</p>
              <p>⚠️ Risk: {item.risk}</p>
              <p>⭐ Priority: {item.priorityScore}</p>
              <p>{item.recommendation}</p>
            </div>
          ))}
        </section>
      )}
    </div>
  );
}

export default App;