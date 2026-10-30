#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

const int CS = D6;
const int DC = D2;
const int RST = D3;
const int VIBRATE = D0;

const int SDA = D10;
const int SCL = D8;

Adafruit_GC9A01A display(CS, DC, RST);
Adafruit_LIS3DH shakey = Adafruit_LIS3DH(); 
WebServer webServer(80);
Preferences storage;

int Current_DOD = 1;
bool wifiActive = false;
bool screenOn = false;
unsigned long displaywakey = 0; 
const unsigned long DISPLAY_TIMEOUT = 10000;

int currentTotalMinutes = 480; 
unsigned long lastMinuteMillis = 0;

struct ClassPeriod {
  int startMinute;
  int endMinute;
  const char* periodName;
};

const ClassPeriod timetable[] = {
  {480, 540, "Period 1"},
  {540, 585, "Period 2"},
  {585, 600, "Break"},
  {600, 645, "Period 3"},
  {645, 690, "Period 4"},
  {690, 735, "Period 5"},
  {735, 780, "Lunch"},
  {780, 820, "Period 6"},
  {820, 860, "Period 7"},
  {860, 900, "Period 8"}
};
const int totalPeriods = sizeof(timetable) / sizeof(timetable[0]);

const char* subjectsDay1[10] = {"PHY", "Chem", "Break", "Eng", "CSC", "Chem prac", "Lunch", "Chem prac", "6th sub", "PT"};
const char* subjectsDay2[10] = {"CS", "MATH", "Break", "CHEM", "VBSE/LBA", "Eng", "Lunch", "PHY", "Chem", "MATH"};
const char* subjectsDay3[10] = {"Math", "Chem", "Break", "Chem", "math", "phy", "Lunch", "PHY", "ENG", "PT"};
const char* subjectsDay4[10] = {"6th sub", "MATH", "Break", "chem", "phy prac", "-", "Lunch", "LIB", "CS", "ENG"};
const char* subjectsDay5[10] = {"Chem", "ENG", "Break", "6th sub", "6th sub", "MATH", "Lunch", "PHY", "CS", "PT"};
const char* subjectsDay6[10] = {"ENG", "MATH", "Break", "6th sub", "PHY", "CS", "Lunch", "Chem", "CS prac", "CS prac"};

String getSubjectName(int day, int index) {
  if (day == 1) return subjectsDay1[index];
  if (day == 2) return subjectsDay2[index];
  if (day == 3) return subjectsDay3[index];
  if (day == 4) return subjectsDay4[index];
  if (day == 5) return subjectsDay5[index];
  if (day == 6) return subjectsDay6[index];
  return "";
}

const char html_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Pocket Watch Timetable</title>
    <style>
        body { font-family: Arial, sans-serif; background: #000000; color: #ffffff; text-align: center; padding: 15px; }
        .card { background: #000000; border: 1px solid #ffffff; padding: 15px; border-radius: 10px; max-width: 450px; margin: auto; }
        h2 { color: #ffffff; font-size: 18px; }
        table { width: 100%; border-collapse: collapse; margin-top: 10px; font-size: 12px; }
        th, td { border: 1px solid #ffffff; padding: 6px; text-align: center; }
        th { background: #ffffff; color: #000000; }
        tr:nth-child(even) { background: #111111; }
    </style>
</head>
<body>

<div class="card">
    <h2 id="DOD">Loading Timetable...</h2>
    <div id="tableContainer"></div>
</div>

<script>
    let userInput = prompt("Enter Day Order (1-6) or 0 for Holiday:");
    let Day_order = Number(userInput);

    let now = new Date();
    let currentHour = now.getHours();
    let currentMinute = now.getMinutes();

    function generateTimetable(day) {
        let titleElem = document.getElementById("DOD");
        let container = document.getElementById("tableContainer");

        if (day === 0) {
            titleElem.innerHTML = "Holiday Today!";
            container.innerHTML = "<p>No classes scheduled.</p>";
            return;
        }

        titleElem.innerHTML = "Day Order " + day + " Timetable";

        let times = [
            "08:00 - 09:00", "09:00 - 09:45", "09:45 - 10:00", 
            "10:00 - 10:45", "10:45 - 11:30", "11:30 - 12:15", 
            "12:15 - 01:00", "01:00 - 01:40", "01:40 - 02:20", "02:20 - 03:00"
        ];
        let periods = [
            "Period 1", "Period 2", "Break", 
            "Period 3", "Period 4", "Period 5", 
            "Lunch", "Period 6", "Period 7", "Period 8"
        ];

        let subjects = [];

        if (day === 1) {
            subjects = ["PHY", "Chem", "Break", "Eng", "CSC", "Chem prac", "Lunch", "Chem prac", "6th sub", "PT"];
        } else if (day === 2) {
            subjects = ["CS", "MATH", "Break", "CHEM", "VBSE/LBA", "Eng", "Lunch", "PHY", "Chem", "MATH"];
        } else if (day === 3) {
            subjects = ["Math", "Chem", "Break", "Chem", "math", "phy", "Lunch", "PHY", "ENG", "PT"];
        } else if (day === 4) {
            subjects = ["6th sub", "MATH", "Break", "chem", "phy prac", "-", "Lunch", "LIB", "CS", "ENG"];
        } else if (day === 5) {
            subjects = ["Chem", "ENG", "Break", "6th sub", "6th sub", "MATH", "Lunch", "PHY", "CS", "PT"];
        } else if (day === 6) {
            subjects = ["ENG", "MATH", "Break", "6th sub", "PHY", "CS", "Lunch", "Chem", "CS prac", "CS prac"];
        } else {
            container.innerHTML = "<p>Invalid Day Order entered.</p>";
            return;
        }

        let htmlTable = "<table><tr><th>Period</th><th>Time</th><th>Subject</th></tr>";
        for (let i = 0; i < periods.length; i++) {
            htmlTable += "<tr><td>" + periods[i] + "</td><td>" + times[i] + "</td><td>" + subjects[i] + "</td></tr>";
        }
        htmlTable += "</table>";

        container.innerHTML = htmlTable;
    }

    function sendToWatch(day, hr, min) {
        fetch('/setDay?val=' + day + '&hr=' + hr + '&min=' + min, { method: 'POST' })
            .then(res => console.log("Config synced."))
            .catch(err => console.error("Error:", err));
    }

    generateTimetable(Day_order);
    if (Day_order >= 0 && Day_order <= 6) {
        sendToWatch(Day_order, currentHour, currentMinute);
    }
</script>

</body>
</html>
)rawliteral";

void triggerVibration(int duration) {
  digitalWrite(VIBRATE, HIGH);
  delay(duration);
  digitalWrite(VIBRATE, LOW);
}

void renderWatchFace(String topText, String mainText, String subText) {
  display.fillScreen(GC9A01A_BLACK);
  display.drawCircle(120, 120, 118, GC9A01A_WHITE);

  display.setTextSize(2);
  display.setTextColor(GC9A01A_WHITE);
  display.setCursor(45, 50);
  display.print(topText);

  display.setTextSize(3);
  display.setTextColor(GC9A01A_WHITE);
  display.setCursor(55, 95);
  display.print(mainText);

  display.setTextSize(2);
  display.setTextColor(GC9A01A_WHITE);
  display.setCursor(50, 150);
  display.print(subText);
}

void checkScheduleAlerts() {
  if (Current_DOD == 0) return;

  int h = currentTotalMinutes / 60;
  int m = currentTotalMinutes % 60;
  String timeStr = (h < 10 ? "0" : "") + String(h) + ":" + (m < 10 ? "0" : "") + String(m);

  for (int i = 0; i < totalPeriods; i++) {
    int warningTime = timetable[i].startMinute - 5;
    int startTime = timetable[i].startMinute;

    if (currentTotalMinutes == warningTime) {
      screenOn = true;
      displaywakey = millis();
      triggerVibration(120);
      delay(100);
      triggerVibration(120);
      String subj = getSubjectName(Current_DOD, i);
      renderWatchFace("5 MIN TO", subj, timeStr);
    } 
    else if (currentTotalMinutes == startTime) {
      screenOn = true;
      displaywakey = millis();
      triggerVibration(350);
      String subj = getSubjectName(Current_DOD, i);
      renderWatchFace("STARTING", subj, timeStr);
    }
  }
}

void turnOffWiFi() {
  webServer.stop();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_OFF);
  wifiActive = false;
  triggerVibration(150);
}

void setup() {
  Serial.begin(115200);
  pinMode(VIBRATE, OUTPUT);

  storage.begin("prefs", true);
  Current_DOD = storage.getInt("dayOrder", 1);
  currentTotalMinutes = storage.getInt("savedMins", 480);
  storage.end();

  display.begin();
  display.setRotation(0);
  display.fillScreen(GC9A01A_BLACK); 

  Wire.begin(SDA, SCL);
  if (shakey.begin(0x18)) {
    shakey.setRange(LIS3DH_RANGE_2_G);
  }

  WiFi.softAP("PocketWatch-Setup", "12345678");
  
  webServer.on("/", []() {
    webServer.send(200, "text/html", html_page);
  });
  
  webServer.on("/setDay", HTTP_POST, []() {
    if (webServer.hasArg("val")) {
      Current_DOD = webServer.arg("val").toInt();
    }
    if (webServer.hasArg("hr") && webServer.hasArg("min")) {
      int hr = webServer.arg("hr").toInt();
      int min = webServer.arg("min").toInt();
      currentTotalMinutes = (hr * 60) + min;
    }
    storage.begin("prefs", false);
    storage.putInt("dayOrder", Current_DOD);
    storage.putInt("savedMins", currentTotalMinutes);
    storage.end();

    webServer.send(200, "text/plain", "OK");
    turnOffWiFi();
  });
  
  webServer.begin();
  wifiActive = true;
  lastMinuteMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (wifiActive) {
    webServer.handleClient();
    if (currentMillis > 2400000) {
      turnOffWiFi();
    }
  }

  if (currentMillis - lastMinuteMillis >= 60000) {
    lastMinuteMillis += 60000;
    currentTotalMinutes++;
    if (currentTotalMinutes >= 1440) {
      currentTotalMinutes = 0;
    }
    checkScheduleAlerts();
  }

  sensors_event_t event;
  shakey.getEvent(&event);
  if (!screenOn && event.acceleration.z > 7.5) {
    screenOn = true;
    displaywakey = currentMillis; 
    triggerVibration(200);          

    int h = currentTotalMinutes / 60;
    int m = currentTotalMinutes % 60;
    String timeStr = (h < 10 ? "0" : "") + String(h) + ":" + (m < 10 ? "0" : "") + String(m);
    
    String currentStatus = "Free Time";
    if (Current_DOD > 0) {
      for (int i = 0; i < totalPeriods; i++) {
        if (currentTotalMinutes >= timetable[i].startMinute && currentTotalMinutes < timetable[i].endMinute) {
          currentStatus = getSubjectName(Current_DOD, i);
          break;
        }
      }
    } else {
      currentStatus = "Holiday";
    }

    renderWatchFace(Current_DOD == 0 ? "HOLIDAY" : "DAY ORDER " + String(Current_DOD), currentStatus, timeStr);
  }

  if (screenOn && (currentMillis - displaywakey > DISPLAY_TIMEOUT)) {
    display.fillScreen(GC9A01A_BLACK);
    screenOn = false;
  }

  delay(100);
}