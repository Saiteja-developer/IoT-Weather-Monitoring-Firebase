# IoT Weather Monitoring System using Firebase

This project collects real-time weather data from the OpenWeather API and uploads it to Firebase Realtime Database.  
The project uses an ESP32, but can also run fully inside Wokwi without any hardware.

---

## Features

- **Fetches real-time weather data for multiple cities**
- **Stores temperature, humidity, pressure, and wind speed**
- **Uploads data to Firebase Realtime Database**
- **Works on ESP32 or Wokwi simulator**
- **Fully cloud-based project**
- **No sensors needed**

---

## Technologies Used

- ESP32 / Wokwi
- OpenWeather REST API
- Firebase Realtime Database
- ArduinoJson Library
- HTTPClient
- Wi-Fi Networking

---

## Project Structure

```
IoT-Weather-Monitoring-Firebase/
│
├── src/
│   ├── weather.ino        # Main ESP32 source code
│
├── README.md              # Documentation
├── .gitignore             # (optional)
└── LICENSE                # (optional)
```

---

## Requirements

- ESP32 board or Wokwi simulator
- Arduino IDE
- Firebase Realtime Database
- OpenWeather API Key
- Internet connection

---

## Setup Instructions

1. **Install Required Libraries in Arduino IDE**
   - ArduinoJson
   - WiFi
   - HTTPClient

2. **Configure WiFi**  
   Update your credentials:
   ```cpp
   const char* ssid = "Wokwi-GUEST";
   const char* password = "";
   ```

3. **Add Your OpenWeather API Key**  
   ```cpp
   String apiKey = "YOUR_API_KEY_HERE";
   ```

4. **Add Your Firebase URL**  
   ```
   https://your-project-id-default-rtdb.firebaseio.com/weather_data.json?auth=YOUR_SECRET
   ```

5. **Upload or Run in Wokwi**  
   Open the project and click Run.

---

## Firebase Data Format

Example JSON stored:
```json
{
  "temperature": 29.4,
  "humidity": 64,
  "pressure": 1012,
  "windSpeed": 2.1,
  "timestamp": 1735642831
}
```

---

## API Used

### OpenWeather Current Weather API

**Base URL:**
```
http://api.openweathermap.org/data/2.5/weather
```

---

## Future Enhancements

- Add more cities dynamically
- Add dashboard (HTML/React/Firebase hosting)
- Add weather alerts
- Store historical logs
- Add auto-sync intervals
