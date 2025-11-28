Below is the simplest possible Python chatbot using the Google Gemini API key (Gemini 1.5 Flash / Pro).
This is a single file, works in terminal, no web framework needed.


---

✅ Install Google Gemini Library

pip install google-generativeai python-dotenv


---

✅ Create .env File

GEMINI_API_KEY=your_api_key_here


---

✅ Simple Python Chatbot Using Gemini

Save this as gemini_chatbot.py

import google.generativeai as genai
from dotenv import load_dotenv
import os

# Load API key
load_dotenv()
genai.configure(api_key=os.getenv("GEMINI_API_KEY"))

# Choose model
model = genai.GenerativeModel("gemini-1.5-flash")

print("Gemini Chatbot (type 'exit' to stop)")

chat_session = model.start_chat(history=[])

while True:
    user_message = input("You: ")

    if user_message.lower() == "exit":
        print("Chatbot: Goodbye!")
        break

    response = chat_session.send_message(user_message)
    print("Chatbot:", response.text)


---

🚀 How It Works

Uses the Gemini 1.5 Flash model (fast + cheap).

Maintains a chat conversation using start_chat().

You type → Gemini replies.

Works for real-world scenarios like:

Customer support

FAQ bot

College admission help bot

Health & fitness assistant

Product recommendation bot




---

❓ Want Next?

I can also give you:

✅ GUI version (Tkinter)
✅ Web chatbot (Flask / FastAPI)
✅ WhatsApp bot version
✅ Telegram bot version
✅ E-commerce customer support bot example

Just tell me!
