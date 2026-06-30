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

const API_URL = "https://last-minute-life-saver-1544232260.asia-south1.run.app";

function App() {
  const [tasks, setTasks] = useState([]);
  const [analytics, setAnalytics] = useState({});
  const [priority, setPriority] = useState([]);
  const [dayPlan, setDayPlan] = useState(null);
  const [aiPlan, setAiPlan] = useState("");
  const hour = new Date().getHours();
  let greeting = "Good Evening";
  if (hour < 12) greeting = "Good Morning";
  else if (hour < 17) greeting = "Good Afternoon";

  const completedPercent=
    analytics.totalTasks >0 
      ? Math.round((analytics.completed / analytics.totalTasks)*100)
      : 0;

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

  const quotes = [
    "Small progress every day leads to big achievements.",
    "Focus on progress, not perfection.",
    "Today's effort is tomorrow's success.",
    "Beat procrastination one task at a time.",
    "Success is built one completed task at a time."
  ];
  const quote = quotes[new Date().getDate() % quotes.length];

  const totalHours = tasks.reduce(
    (sum, task) => sum + Number(task.estimatedHours || 0),
    0
  );
  const highPriority = tasks.filter(
    (task) => task.importance === "High"
  ).length;
  const nextTask =
    priority.length > 0 ? priority[0].title : "No tasks available";
  
  const focusTask =
    priority.length > 0
      ? priority[0]
      : tasks.find((t) => t.status !== "Completed");

  return (
    <div className="app">
      <section className="hero">
        <h1>🚀 Last-Minute Life Saver</h1>
        <p>
          AI-powered productivity planner built for students.
        </p>
        <div className="badge">
          🤖 Powered by Gemini AI + Smart Priority Engine
          </div>
      </section>
    <h2 style={{ marginTop: "25px" }}>
      👋{greeting}!
    </h2>

<p className="subtitle">{quote}</p>
{focusTask && (
  <section className="focus-card">
    <h2>🎯 Today's Focus</h2>
    <h3>{focusTask.title}</h3>
    <p>⏰ Estimated Time: {focusTask.estimatedHours} hrs</p>
    <p>📅 Deadline: {focusTask.deadline}</p>
    <p>⭐ Priority: {focusTask.importance}</p>
    <div className="focus-tip">
      🤖 AI Recommendation:
      <br />
      Complete this task first to reduce deadline risk and improve today's productivity.
    </div>
  </section>
)}

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
        <div>
          <span>📋</span>
          <h3>{analytics.totalTasks ?? 0}</h3>
          <p>Total Tasks</p>
        </div>
        <div>
          <span>✅</span>
          <h3>{analytics.completed ?? 0}</h3>
          <p>Completed</p>
        </div>
        <div>
          <span>⏳</span>
          <h3>{analytics.pending ?? 0}</h3>
          <p>Pending</p>
        </div>

        <div>
          <span>⏭️</span>
          <h3>{analytics.skipped ?? 0}</h3>
          <p>Skipped</p>
        </div>

        <div>
          <span>🔥</span>
          <h3>{completedPercent}%</h3>
          <p>Productivity</p>
        </div>
      </section>
      <section className="card">
        <h2>📈 Productivity Progress</h2>
        <div className="progress-bar">
          <div
            className="progress-fill"
            style={{ width: `${completedPercent}%` }}
          ></div>
        </div>
        <p className="progress-text">
          You have completed {completedPercent}% of your tasks.
        </p>
      </section>

      <section className="card">
        <h2>Tasks</h2>
        {tasks.length === 0 && (
          <p className="empty-state">
            📅 No tasks yet. Add your first task and let AI plan your day.
          </p>
        )}
        {tasks.map((task) => (
          <div
            className={`task ${
              task.importance === "High"
              ? "high"
              : task.importance === "Medium"
              ? "medium"
              : "low"
            }`}
            key={task.id}
          >
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
        {priority.length === 0 && (
          <p className="empty-state">
            🤖 Add tasks to see AI priority recommendations.
          </p>
        )}
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

      <section className="card">
        <h2>🤖 AI Insights</h2>
        <div className="insights">
          <div className="insight">
            📋 <strong>{tasks.length}</strong> tasks scheduled
          </div>
          <div className="insight">
            <strong>{totalHours}</strong> hours remaining
          </div>
          <div className="insight">
            🔥 <strong>{highPriority}</strong> high priority tasks
          </div>
          <div className="insight">
            🎯 Suggested next task:
            <br />
            <strong>{nextTask}</strong>
          </div>
        </div>
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
      <footer>
        Built with ❤️ using React, C++, Gemini AI and Google Cloud
      </footer>
    </div>
  );
}

export default App;