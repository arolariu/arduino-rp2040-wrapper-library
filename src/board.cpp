#include "board.hpp"

Board::Board(
    uint8_t buttonPin, uint8_t buttonLedPin,
    uint8_t buzzerPin,
    uint8_t joystickXPin, uint8_t joystickYPin,
    uint8_t ledRingPin, uint8_t ledRingBulbs) {
    button = new Button(buttonPin, buttonLedPin);
    buzzer = new Buzzer(buzzerPin);
    ledRing = new LedRing(ledRingBulbs, ledRingPin);
    display = new Display();
    joystick = new Joystick(joystickXPin, joystickYPin);
}


ButtonType Board::checkButtonType() {
    return button->checkButtonState();
}

void Board::solidLedRing(const uint32_t &color) {
    ledRing->solidColor(color);
}

void Board::flashLedRing(const uint32_t &color, const uint8_t &times, const uint8_t &waitTime) {
    ledRing->flashColor(color, times, waitTime);
}

void Board::clearDisplay() {
    display->clearDisplay();
}

void Board::displayTime(const uint8_t &lineNumber) {
    unsigned long epochTime = WiFi.getTime();
    unsigned long hours = (epochTime % 86400L) / 3600;
    unsigned long minutes = (epochTime % 3600) / 60;
    unsigned long seconds = epochTime % 60;

    char* time = (char*)calloc(15, sizeof(char));
    time[0] = 'T';
    time[1] = 'i';
    time[2] = 'm';
    time[3] = 'e';
    time[4] = ':';
    time[5] = ' ';
    time[6] = '0' + hours / 10;
    time[7] = '0' + hours % 10;
    time[8] = ':';
    time[9] = '0' + minutes / 10;
    time[10] = '0' + minutes % 10;
    time[11] = ':';
    time[12] = '0' + seconds / 10;
    time[13] = '0' + seconds % 10;
    time[14] = '\0';

    display->setLineText(lineNumber, time);
}

void Board::displayDate(const uint8_t &lineNumber) {
    time_t time = WiFi.getTime();
    struct tm *timeinfo = gmtime(&time);
    char *date = (char*)calloc(18, sizeof(char));
    sprintf(date, "Date: %02d/%02d/%04d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

    display->setLineText(lineNumber, date);
}

void Board::setDisplayLine(const uint8_t &lineNumber, const char *text) {
    display->setLineText(lineNumber, text);
}

JoystickDirection Board::getJoystickDirection() {
    return joystick->getDirection();
}

JoystickCoords Board::getJoystickCoords() {
    return joystick->getCoords();
}

Board::~Board() {
    if (button != nullptr) delete button;
    if (buzzer != nullptr) delete buzzer;
    if (ledRing != nullptr) delete ledRing;
    if (display != nullptr) delete display;
}
