#include "../include/httplib.h"
#include "../include/json.hpp"

#include "GeminiService.h"
#include "../services/PriorityEngine.h"
#include "../services/RiskAnalyzer.h"
#include "../services/RecommendationEngine.h"
#include "../utils/DateUtils.h"

#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;

string getApiKey()
{
    ifstream file("../.env");
    string line;

    while (getline(file, line))
    {
        if (line.find("GEMINI_API_KEY=") == 0)
        {
            return line.substr(15);
        }
    }

    return "";
}

string GeminiService::generateDayPlan(const vector<Task>& tasks)
{
    string apiKey = getApiKey();

    if (apiKey.empty())
    {
        return "Gemini API key not found. Please check backend-cpp/.env";
    }

    json taskData = json::array();

    for (auto &task : tasks)
    {
        taskData.push_back({
            {"title", task.title},
            {"deadline", task.deadline},
            {"estimatedHours", task.estimatedHours},
            {"importance", task.importance},
            {"status", task.status},
            {"priorityScore", PriorityEngine::calculatePriority(task)},
            {"risk", RiskAnalyzer::getRiskLevel(task)},
            {"daysRemaining", DateUtils::daysUntil(task.deadline)},
            {"recommendation", RecommendationEngine::getRecommendation(task)}
        });
    }

    string prompt =
        "You are Last-Minute Life Saver, an AI productivity coach. "
        "Create a practical day plan from these tasks. "
        "Prioritize high-risk and high-priority work. "
        "Give time blocks, explain the order, and give motivating advice. "
        "Keep it concise and student-friendly.\n\nTasks:\n" +
        taskData.dump(2);

    json requestBody = {
        {"contents", {{
            {"parts", {{
                {"text", prompt}
            }}}
        }}}
    };

    httplib::SSLClient client("generativelanguage.googleapis.com");
    client.set_follow_location(true);

    string path =
        "/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey;

    auto result = client.Post(
        path.c_str(),
        requestBody.dump(),
        "application/json"
    );

    if (!result)
    {
        return "Gemini request failed. Please check internet connection or SSL setup.";
    }

    json response = json::parse(result->body, nullptr, false);

    if (response.is_discarded())
    {
        return "Could not parse Gemini response.";
    }

    if (response.contains("error"))
    {
        string plan =
        "🤖 Local AI Productivity Coach\n\n";
        for (const auto &task : tasks)
        {
            if (task.status != "Completed")
            {
                plan += "📌 " + task.title + "\n";
                plan += "• Priority: " +
                    to_string(PriorityEngine::calculatePriority(task)) + "\n";
                plan += "• Risk: " +
                    RiskAnalyzer::getRiskLevel(task) + "\n";
                plan += "• Recommendation: " +
                    RecommendationEngine::getRecommendation(task) + "\n\n";
            }
        }
        plan +=
        "💡 Since Gemini is temporarily unavailable, this plan was generated "
        "using the built-in C++ AI decision engine.";
        return plan;
    }

    return response["candidates"][0]["content"]["parts"][0]["text"];
}