# Last-Minute Life Saver
Problem Statement Selected
Students often struggle to manage multiple academic, personal, and career-related tasks simultaneously, leading to missed deadlines, poor prioritization, and increased stress. Existing to-do list applications primarily focus on task tracking but lack intelligent prioritization and personalized guidance. The objective of this project is to develop an AI-powered productivity assistant that analyzes task urgency and importance, recommends an optimal execution order, and generates personalized daily study plans to improve productivity and reduce last-minute workload.

# Solution Overview
Last-Minute Life Saver is an AI-powered productivity planner designed specifically for students. The application enables users to efficiently organize, prioritize, and track their tasks while receiving intelligent recommendations based on urgency, deadlines, and importance.
Users can add tasks along with their deadlines, estimated completion time, category, and importance level. The backend processes this information using a custom priority engine and risk analysis algorithm to determine which tasks require immediate attention.
The application also integrates Google's Gemini API to generate personalized AI-powered daily study plans that recommend an optimized schedule, explain why tasks should be completed in a particular order, and provide motivational guidance.
In addition to task management, the application offers productivity analytics, helping users monitor completed tasks, pending work, and overall progress through an intuitive dashboard.

# Key Features
AI-powered personalized daily planner using Gemini API
Intelligent task prioritization based on urgency and importance
Risk analysis for identifying high-priority and overdue tasks
Smart recommendations for effective task scheduling
Add, update, and manage tasks efficiently
Real-time productivity analytics and dashboard
Progress tracking and completion statistics
Student-friendly responsive user interface
Cloud-based deployment for easy accessibility

# Technologies Used
Frontend
React.js
Vite
Axios
CSS3
React Icons
Backend
C++
cpp-httplib
nlohmann/json
CMake
REST APIs
Development Tools
Git
GitHub
Docker

# Google Technologies Utilized
This project leverages multiple Google technologies for AI capabilities and cloud deployment:
Google Gemini API
Used to generate personalized AI-based productivity plans. The Gemini model analyzes the user's task list and produces optimized schedules, prioritization strategies, and motivational suggestions.
Google Cloud Run
The C++ backend is containerized using Docker and deployed as a serverless service on Google Cloud Run, providing scalable and reliable API hosting.
Firebase Hosting
The React frontend is deployed using Firebase Hosting, enabling secure HTTPS hosting, fast global content delivery, and seamless integration with the Cloud Run backend.
Google Cloud Build
Cloud Build automatically builds the Docker container from the GitHub repository and prepares it for deployment on Cloud Run.
Artifact Registry
Stores the generated Docker container images used during deployment to Cloud Run.

# Project Architecture
User
  │
  ▼
Firebase Hosting (React Frontend)
https://hackathon-501016.web.app
  │
  ▼
Cloud Run (C++ Backend APIs)
  │
  ├── Task Management
  ├── Priority Engine
  ├── Risk Analyzer
  ├── Analytics Engine
  └── Gemini AI Integration
           │
           ▼
    Google Gemini API

# Deployment Links
Frontend (Firebase Hosting)
https://hackathon-501016.web.app
Backend (Google Cloud Run)
https://last-minute-life-saver-1544232260.asia-south1.run.app
GitHub Repository
https://github.com/shineyrbl-byte/last-minute-life-saver

# Future Enhancements
User authentication using Firebase Authentication
Cloud Firestore integration for persistent task storage
Calendar synchronization with Google Calendar
Email and push notification reminders
AI-powered weekly productivity reports
Team collaboration and shared task management
Mobile application support
Machine learning-based personalized productivity recommendations
